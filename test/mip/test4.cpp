#include "../help.hpp"

int main(int argc, char** argv)
{
    anyprog::optimization::function_t obj = [&](const anyprog::real_block& x) {
        return 2 * x(0) + x(1);
    };

    std::vector<anyprog::optimization::inequation_condition_function_t> ineq = {
        [](const anyprog::real_block& x) {
            return 1.25 - x(0) * x(0) - x(1);
        },
        [](const anyprog::real_block& x) {
            return x(0) + x(1) - 1.6;
        }

    };

    std::vector<anyprog::optimization::range_t> range = { { 0, 1.6 }, { 0, 1 } };

    anyprog::optimization opt(obj, range);
    opt.set_inequation_condition(ineq);
    opt.set_filter_function([](anyprog::real_block& x) {
        x(1) = round(x(1));
    });
    auto ret = opt.search(5, 3);
    anyprog::print(opt.is_ok(), ret, obj);
    return 0;
}