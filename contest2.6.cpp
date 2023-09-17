// #include <vector>
// #include <algorithm>
// std::vector<int> kSmallest(std::vector<int> v, std::size_t k){
// 	std::vector<int> ret;
// 	std::nth_element(v.begin(), v.begin() + k, v.end());
// 	for (std::size_t i = 0; i < k; ++i){
// 		ret.push_back(v[i]);
// 	}
// 	return ret;
// }

#include <iostream>
#include <map>
#include <vector>
#include <stack>
#include <queue>
#include <cstdint>
#include <utility>
#include <algorithm>

// using V = std::uint64_t;

// int main()
// {
//     std::map<V, std::vector<std::pair<V, V>>> graph;

//     V a, b, w;
//     while(std::cin >> a >> b >> w)
//     {
//         graph[a].push_back(std::pair<V, V>(b, w));
//         graph[b].push_back(std::pair<V, V>(a, w));
//     }

//     // std::vector<bool> visited(graph.size(), false);
//     std::vector<V> weights(graph.size(), false);
//     std::stack<V> s;

//     s.push(0);
//     // visited[0] = true;
//     weights[0] = 0;
//     for (int i = 1; i < graph.size(); ++i)
//     {
//     	weights[i] = -1;
//     }

//     while(!s.empty())
//     {
//         V const i = s.top();
//         s.pop();

//         for(std::pair<V, V> const j : graph[i])
//         {
//         	if(weights[i] + j.second < weights[j.first]){
//         		weights[j.first] = weights[i] + j.second;
//         		s.push(j.first);
//         	}
//             // if(!visited[j])
//             // {
//             //     visited[j] = true;
//             //     s.push(j);
//             // }

//         }
//     }
//     // std::cout << (visited[graph.size() - 1] ? "true" : "false") << std::endl;
//     for (std::size_t i = 0; i < graph.size(); ++i)
//     {
//     	std::cout << weights[i] << " ";
//     }
//     std::cout << std::endl;
// }

class PiecewiseLinearFunction
{
    using Point = std::pair<double, double>;
    std::vector<Point> data;
public:
    template<typename It>
    PiecewiseLinearFunction(It begin, It end) noexcept
        : data(begin, end)
    {}
    double operator()(double const x) const;
};

double PiecewiseLinearFunction::operator()(double const x) const{
	if(x <= this->data[0].first){
		return this->data[0].second;
	}
	if(x >= this->data.back().first){
		return this->data.back().second;
	}
	auto cmp = [](Point a, Point b){return a.first < b.first;};
	auto i = std::lower_bound(this->data.begin(), this->data.end(), std::pair<double, double>{x, 0.}, cmp) - this->data.begin() - 1;
	double t = (x - this->data[i].first) / (this->data[i+1].first - this->data[i].first); 
	return (1 - t) * this->data[i].second + t * this->data[i + 1].second; 
}

int main(){
	std::pair<double, double> a[] =
	{
		{-1., 0.},
	    {0., 1.},
	    {1., 2.},
	    {3., 6.},
	};
	PiecewiseLinearFunction const f = {a, a + 4};
	std::cout << f(0) << std::endl;
	// std::cout << f(1) << " " << f(2) << " " << f(3) << std::endl;
}