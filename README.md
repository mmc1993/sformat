# sformat
这是一个超级轻量级的 C++ String Format 实现

This is a super lightweight C++ String Format implementation


示例：

//  c++ code
auto str = SFormat("hello world, {0}, {0}, {1}, {2}, {3}", 123, 1.23, "123", std::string("123"));

//  output:
hello world, 123, 123, 1.23, 123, 123
