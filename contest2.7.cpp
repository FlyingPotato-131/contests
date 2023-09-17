class Point
{
protected:
    double _x;
    double _y;
    double _z;

public:
    Point(double x, double y, double z): _x(x), _y(y), _z(z) {
    }
    
    double x() const {
        return _x;
    }

    double y() const {
        return _y;
    }

    double z() const {
        return _z;
    }
};

Point operator-(Point a, Point b){
    return {a.x() - b.x(), a.y() - b.y(), a.z() - b.z()};
}

double abs(Point a){
    return a.x() * a.x() + a.y() * a.y() + a.z() * a.z();
}

class Sphere
{
    Point center;
    double r;
public:
    Sphere(const Point& center, double r): center(center), r(r){}
    
    // Проверка, попадает ли заданная точка p в данную сферу.
    // (Расстояния сравнивать с точностью 1e-6.)
    bool covers(const Point& p) const{
        return abs(p - center) < r * r;
    }
};

#include <iostream>

// int main(){
//     Point center(10.0, 10.0, 10.0);
//     Sphere s(center, 0.5);

//     // Создаём пару тестовых точек
//     Point p1(10.1, 10.1, 10.1);
//     Point p2(2, 2, 2);

//     // Ожидаем, что первая точка внутри сферы
//     std::cout << std::boolalpha << s.covers(p1) << std::endl;
//     // Ожидаем, что вторая точка не попала внутрь сферы
//     std::cout << std::boolalpha << s.covers(p2) << std::endl;
// }


class MoneyBox {
    unsigned int money = 0;
    unsigned int coins = 0;
public:
    // Конструктор и деструктор, если нужны

    // Добавить монетку достоинством value
    void addCoin(unsigned int value){
        money += value;
        coins++;
    }

    // Получить текущее количество монеток в копилке
    unsigned int getCoinsNumber() const{
        return coins;
    }

    // Получить текущее общее достоинство всех монеток
    unsigned int getCoinsValue() const{
        return money;
    }
};

// int main(){
//     MoneyBox m;
//     // Добавили монетку достоинством 10
//     m.addCoin(10);
//     // Добавили монетку достоинством 5
//     m.addCoin(5);

//     // Ожидаем, что монеток внутри 2 штуки
//     std::cout << m.getCoinsNumber() << std::endl;
//     // Ожидаем, что общее достоинство всех монеток 15
//     std::cout << m.getCoinsValue() << std::endl;
// }

#include <stdexcept>

class GasStation {
    unsigned int volume;
    unsigned int gas;
public:
    // Конструктор, принимающий один параметр - ёмкость резервуара колонки
    // Резервуар создаётся пустой
    GasStation(unsigned int v) : volume(v), gas(0){}

    // Залить в резервуар колонки n литров топлива
    // Если столько не влезает в резервуар - не заливать ничего, выбросить std::exception
    void fill(unsigned int n){
        if(volume >= n + gas){
            gas += n;
        }else{
            throw std::exception();
        }
    }

    // Заправиться, забрав при этом из резервура n литров топлива
    // Если столько нет в резервуаре - не забирать из резервуара ничего, выбросить std::exception
    void tank(unsigned int n){
        if(gas >= n){
            gas -= n;
        }else{
            throw std::exception();
        }
    }

    // Запросить остаток топлива в резервуаре
    unsigned int get_limit() const{
        return gas;
    }
};

// int main(){
//     GasStation s = GasStation(1000);            // Колонка на 1000, пока пустая
//     s.fill(300);                                // Это влезет в резервуар, 
//     std::cout << s.get_limit() << std::endl;              // ... так что здесь увидим на экране 300.

//     s.tank(100);                                // Забрали из резервуара 100, 
//     s.fill(300);                                // ... после чего долили ещё 300,
//     std::cout << s.get_limit() << std::endl;              // ... так что на экране ожидаем 500.

//     for(unsigned int i = 0; i < 5; i++)         // В цикле забрали 5 раз по 50,
//         s.tank(50);
//     std::cout << s.get_limit() << std::endl;              // ... так что на экране ожидаем 250.

//     s.fill(1000);                               // А вот тут ожидаем exception.
//                                                 // (После проверки exception-а строку стоит просто убрать.)

//     for(unsigned int i = 0; i < 50; i++) {      // Теперь пытаемся забрать 50 раз по 100,
//         s.tank(100);                            // из-за чего на третьей попытке ждём exception. 
//         std::cout << s.get_limit() << std::endl;
//     }
// }

#include <map>

// int main(){
//     unsigned int len;
//     std::cin >> len;
//     std::map<int, bool> nums;
//     for (unsigned int i = 0; i < len; ++i){
//         int n;
//         std::cin >> n;
//         if(nums.find(n) == nums.end())
//             nums.emplace(n, false);
//         else
//             nums[n] = true;
//     }
//     auto it = nums.end();
//     it--;
//     while (it->second){
//         it--;
//     }
//     std::cout << it->first << std::endl;
// }

#include <string>
#include <set>
#include <algorithm>

// std::string strlow(std::string str){
//     for (std::size_t i = 0; i < str.size(); ++i){
//         str[i] = std::tolower(str[i]);
//     }
//     return str;
// }

// int main(){
//     unsigned int len;
//     std::cin >> len;
//     std::map<std::string, std::set<std::string>> words;
//     for (unsigned int i = 0; i < len; ++i){
//         std::string str;
//         std::cin >> str;
//         // std::cout << strlow(str);
//         if(words.find(strlow(str)) != words.end()){
//             auto it = words.find(strlow(str));
//             it->second.emplace(str);
//         }else{
//             words.emplace(strlow(str), std::set<std::string>(&str, &str + 1));
//         }
//     }
//     // for (auto it : words){
//     //     std::cout << it.first << " ";
//     // }
//     // std::cout << std::endl;
//     std::map<std::size_t, std::set<std::string>, std::greater<std::size_t>> sorted;
//     for(auto it : words){
//         if(sorted.find(it.second.size()) == sorted.end())
//             sorted.emplace(it.second.size(), std::set<std::string>(&it.first, &it.first + 1));
//         else
//             sorted[it.second.size()].emplace(it.first);
//     }
//     for(auto it : sorted){
//         if(it.first > 2)
//             for(auto str : it.second)
//                 std::cout << str << std::endl;
//     }
// }

// class ResultsHolder {
//     std::map<std::string, unsigned int> results;
// public:
//     /**
//      * Добавить в общую таблицу результат экзамена студента. 
//      * Параметры:
//      * - full_name - строка с полным именем студента
//      * - mark - оценка (от 1 до 10)
//      * (Гарантируется, что совпадений полных имён у разных студентов не бывает.)
//      * 
//      * Если студента с данным именем нет в результатах - добавить его.
//      * Если студент с таким именем есть - обновить его результат 
//      * (потому что апелляции вполне возможны).
//      */
//     void update(const std::string& full_name, unsigned mark){
//         results[full_name] = mark;
//     }

//     /**
//      * Вывести студентов, отсортировав по именам по алфавиту.
//      *
//      * Вывод в std::cout.
//      *
//      * Формат вывода:
//      * Alex 7
//      * Anastasia 9
//      * Anny 5
//      * Ivan 10
//      * Nikita 8
//      */
//     void print_students() const{
//         for(auto it : results){
//             std::cout << it.first << " " << it.second << std::endl;
//         }
//     }

//     /**
//      * Вывести студентов, отсортировав сперва по оценкам по убыванию,
//      * а при равных оценках - по именам по алфавиту.
//      *
//      * Вывод в std::cout.
//      *
//      * Формат вывода:
//      * Ivan 10
//      * Anastasia 9
//      * Nikita 8
//      * Alex 7
//      * Anny 5
//      */
//     void print_standings() const{
//         std::map<unsigned int, std::set<std::string>, std::greater<unsigned int>> sorted;
//         for(auto it : results){
//             if(sorted.find(it.second) == sorted.end())
//                 sorted.emplace(it.second, std::set<std::string>(&it.first, &it.first + 1));
//             else
//                 sorted[it.second].emplace(it.first);
//         }
//         for(auto it : sorted)
//             for(auto name : it.second)
//                 std::cout << name << " " << it.first << std::endl;
//     }

//     /**
//      * Обработать запрос военкомата.
//      *
//      * Военкомат передаёт список имён и хочет призвать этих людей в армию.
//      * Если у этих людей неуд-ы (оценка ниже 3), то:
//      * - вернуть эти имена в ответе военкомату;
//      * - удалить этих людей из общей таблицы (потому что теперь они не студенты).
//      *
//      * Входной параметр: сет строк с именами, кого хочет призвать военкомат.
//      * Возвращаемое значение: сет строк с именами, кого действительно можно призвать
//      * (или пустой сет, если призвать никого нельзя).
//      * Гарантируется, что военкомат не будет пытаться призвать несуществующих студентов.
//      */
//     std::set<std::string> process_military_request(const std::set<std::string>& names){
//         std::set<std::string> ret;
//         for(auto it : names){
//             if(results[it] < 3 && (names.find(it) != names.end())){
//                 ret.emplace(it);
//                 results.erase(it);
//             }
//         }
//         return ret;
//     }
// };

// int main(){
//     ResultsHolder rh;

//     // Загрузили результаты
//     rh.update("Alex", 6);
//     rh.update("Anny", 5);
//     rh.update("Ivan", 10);
//     rh.update("Anastasia", 9);
//     rh.update("Johnny", 1);
//     rh.update("Alex", 7); // Апелляция у Alex, оценка обновляется
//     rh.update("Nikita", 8);

//     // Вывели в порядке убывания результата
//     std::cout << "Exam results:" << std::endl;
//     rh.print_standings();

//     // Определили, кто идёт в армию
//     auto to_military_service = rh.process_military_request({"Johnny", "Ivan"});

//     // Вывели их на экран
//     std::cout << "Are in army now:" << std::endl;
//     for(const auto& s : to_military_service) {
//         std::cout << s << std::endl;
//     }

//     // Вывели по алфавиту (но уже без Johnny, но Ivan остался с нами)
//     std::cout << "Exam results:" << std::endl;
//     rh.print_students();
// }

class Ball {
    enum state{
        Intact = 0;
        Destroyed = 1;
        Lost = 2;
    }state = Intact;

public:
    // Конструктор и деструктор шара, если нужны

    // Попытка сломать шар.
    // Для первого целого шара должна заканчиваться успешно.
    // Если один шар уже был сломан, выбросить std::exception
    // Если пытаемся ломать уже сломанный или потерянный шар, выбросить std::exception
    void destroy(){
        static bool destroyed = false;
        if(!destroyed && state != Destroyed && state != Lost){
            destroyed = true;
            state = 1;
        }else{
            throw std::exception();
        }
    }

    // Попытка потерять шар.
    // Для первого целого шара должна заканчиваться успешно.
    // Если один шар уже был потерян, то выбросить std::exception
    // Если пытаемся терять уже сломанный или потерянный шар, выбросить std::exception
    void lose(){
        static bool lost = false;
        if(!lost && state != Destroyed && state != Lost){
            lost = true;
            state = 2;
        }else{
            throw std::exception();
        }
    }
};