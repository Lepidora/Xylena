#pragma once

//Task and block definition
#define Task std::function<void()>
#define block(code) [](){code;}