#include <algorithm>
#include <cmath>
#include <fstream>
#include <random>

struct vec4{
    float x, y, z, w;
};

vec4 operator+(vec4 const &a, vec4 const &b) {return {a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w};}
vec4 operator-(vec4 const &a, vec4 const &b) {return {a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w};}
vec4 operator*(vec4 const &a, vec4 const &b) {return {a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w};}
vec4 operator/(vec4 const &a, vec4 const &b) {return {a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w};}
float      dot(vec4 const &a, vec4 const &b) {return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;}
float    dist2(vec4 const &a, vec4 const &b) {return dot(a - b, a - b);}

vec4 min(vec4 const &a, vec4 const &b){
    return
    {
        a.x < b.x ? a.x : b.x,
        a.y < b.y ? a.y : b.y,
        a.z < b.z ? a.z : b.z,
        a.w < b.w ? a.w : b.w,
    };
}

vec4 max(vec4 const &a, vec4 const &b){
    return
    {
        a.x < b.x ? b.x : a.x,
        a.y < b.y ? b.y : a.y,
        a.z < b.z ? b.z : a.z,
        a.w < b.w ? b.w : a.w,
    };
}

struct AABB{
    vec4 min, max;
};

AABB toBox(vec4 const &p) {return {p, p};}
AABB operator+(AABB const &a, AABB const &b){
    return
    {
        min(a.min, b.min),
        max(a.max, b.max),
    };
}

struct Node{
    struct Kids
    {
        Node const *left;
        Node const *right;
    };
    virtual ~Node() = default;
    virtual AABB box() const = 0;
    virtual Kids const *pKids () const {return nullptr;}
    virtual vec4 const *pPoint() const {return nullptr;}
};

class Leaf : public Node{
    vec4 point;
public:
    Leaf(vec4 const &p)
        : point(p)
    {}
    AABB           box() const override {return toBox(point);}
    vec4 const *pPoint() const override {return &point;}
};

class Parent : public Node{
    AABB aabb;
    Kids kids;
public:
    ~Parent() override
    {
        delete kids. left;
        delete kids.right;
    }
    Parent(Node const *left, AABB const &b, Node const *right)
        : aabb(b)
        , kids{left, right}
    {}
    AABB          box() const override {return  aabb;}
    Kids const *pKids() const override {return &kids;}
};

#include <cassert>
#include <algorithm>
template<typename RandomIt>
Node const *createTree(RandomIt const begin, RandomIt const end){
    assert(begin < end);
    if(end - begin == 1)
        return new Leaf(*begin);
    AABB box = toBox(*begin);
    for(RandomIt it = begin + 1; it != end; ++it)
        box = box + toBox(*it);
    using Compare = bool(vec4, vec4);
    Compare const *less[] =
    {
        +[](vec4 a, vec4 b) {return a.x < b.x;},
        +[](vec4 a, vec4 b) {return a.y < b.y;},
        +[](vec4 a, vec4 b) {return a.z < b.z;},
        +[](vec4 a, vec4 b) {return a.w < b.w;},
    };
    RandomIt const mid = begin + (end - begin) / 2;
    vec4 const diag = box.max - box.min;
    float const * const x = &diag.x;
    std::nth_element(begin, mid, end, less[std::max_element(x, x + 4) - x]);
    return new Parent(createTree(begin, mid), box, createTree(mid, end));
}

// vec4 nearestFrom(vec4 const &p, Node const * const tree)
// {
//     Node::Kids const * const kids = tree->pKids();
//     if(nullptr == kids)
//         return *tree->pPoint();
//     else
//     {
//         vec4 const l = nearestFrom(p, kids->left );
//         vec4 const r = nearestFrom(p, kids->right);
//         return dist2(p, l) < dist2(p, r) ? l : r;
//     }
// }

float boxDistance2(AABB box, vec4 v){
    float dx, dy, dz, dw;
    if(v.x <= box.min.x)
        dx = box.min.x - v.x;
    else if(v.x <= box.max.x)
        dx = 0;
    else //if(v.x >= box.max.x)
        dx = v.x - box.max.x;
    if(v.y <= box.min.y)
        dy = box.min.y - v.y;
    else if(v.y <= box.max.y)
        dy = 0;
    else //if(v.y >= box.max.y)
        dy = v.y - box.max.y;
    if(v.z <= box.min.z)
        dz = box.min.z - v.z;
    else if(v.z <= box.max.z)
        dz = 0;
    else //if(v.z >= box.max.z)
        dz = v.z - box.max.z;
    if(v.w <= box.min.w)
        dw = box.min.w - v.w;
    else if(v.w <= box.max.w)
        dw = 0;
    else //if(v.w >= box.max.w)
        dw = v.w - box.max.w;
    return dx * dx + dy * dy + dz * dz + dw * dw;
}

vec4 nearestFrom(vec4 const &p, Node const * const tree){
    Node::Kids const * const kids = tree->pKids();
    if(kids == nullptr)
        return *tree->pPoint();
    else{
        float ldist = boxDistance2(kids->left->box(), p);
        float rdist = boxDistance2(kids->right->box(), p);
        vec4 mindist = nearestFrom(p, ldist < rdist ? kids->left : kids->right);
        if(dist2(mindist, p) <= (ldist < rdist ? rdist : ldist))
            return mindist;
        else{
            vec4 maxdist = nearestFrom(p, ldist < rdist ? kids->right : kids->left);
            return dist2(p, mindist) < dist2(p, maxdist) ? mindist : maxdist;
        }
    }
}

#include <iostream>
#include <fstream>
#include <cmath>
#include <random>
int main()
{
    std::mt19937 gen;
    std::uniform_real_distribution<float> dist;
    std::vector<vec4> v;
    for(unsigned int i = 0u; i < 100000u; ++i)
        v.push_back({dist(gen), dist(gen), dist(gen), dist(gen)});
    Node const * const tree = createTree(v.begin(), v.end());
    unsigned int const width  = 1600u;
    unsigned int const height = 1600u;
    std::ofstream out("out.ppm");
    out << "P3\n" << width << ' ' << height << "\n255" << std::endl;
    for(unsigned int y = 0u; y < height; ++y)
    for(unsigned int x = 0u; x <  width; ++x)
    {
        float const fx = float(x) / (width  - 1u);
        float const fy = float(y) / (height - 1u);
        vec4 const p = nearestFrom({fx, fy, 0.3f, 0.5f}, tree);
        out << std::round(p.x * 255.f) << ' ';
        out << std::round(p.y * 255.f) << ' ';
        out << std::round(p.z * 255.f) << ' ';
    }
    delete tree;
}