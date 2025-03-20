#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <cstdint>
#include <cctype>

// Кодирования 4 байт ASCII85
std::string encode_bytes(const std::vector<std::uint8_t>& bytes) {
    std::uint32_t val = 0;
    for (std::size_t i = 0; i < bytes.size(); ++i) {
        val = (val << 8) | bytes[i]; // Сдвигаем значение на 8 бит влево и добавляем текущий байт
    }
    std::string res;
    for (int i = 0; i < 5; ++i) {
        res = char(val % 85 + 33) + res; // Смещаем на значение "!"
        val /= 85;
    }
    return res;
}

// Кодирования ASCII85
std::string ascii85_encode(const std::vector<std::uint8_t>& data) {
    std::string res = "";
    for (std::size_t i = 0; i < data.size(); i += 4) {
        std::vector<std::uint8_t> bytes; // Храним 4 байта
        for (std::size_t j = 0; j < 4; ++j) {
            if (i + j < data.size()) { // Проверка на выход за пределы
                bytes.push_back(data[i + j]); // Заполняем байтами
            } else {
                bytes.push_back(0); // Заполняем нулями
            }
        }
        res += encode_bytes(bytes);
    }
    return res;
}

// Декодирования 4 байт ASCII85 
std::vector<std::uint8_t> decode_bytes(const std::string& bytes) {
    std::uint32_t val = 0;
    for (char c : bytes) {
        val = (c - 33) + val * 85; // Сдвигаем на значение "!"
    }
    std::vector<std::uint8_t> res(4); // 4 байта на результат
    for (int i = 3; i >= 0; --i) {
        res[i] = (val & 0xFF); // Получаем результат используя битовую маску 
        val = (val >> 8); // Сдвигаем текущее значение на 8 бит вправо
    }
    return res;
}

// Декодирования ASCII85
std::vector<std::uint8_t> ascii85_decode(const std::string& encoded) {
    std::string data = encoded;
    std::vector<std::uint8_t> res;
    for (std::size_t i = 0; i < data.size(); i += 5) {
        std::string bytes = data.substr(i, 5); // Получаем подстроку из 5 символов
        std::vector<std::uint8_t> decoded_bytes = decode_bytes(bytes);
        // Удаляем лишние байты, добавленные при кодировании
        if (i + 5 > data.size() && data.size() % 5 != 0) {
            std::size_t remaining = data.size() % 5;
            if (remaining > 0) {
                decoded_bytes.resize(remaining - 1); // Удаляем лишние байты
            }
        }
        res.insert(res.end(), decoded_bytes.begin(), decoded_bytes.end()); // Добавляем декодированные байты к результату
    }
    return res;
}

int main(int argc, char* argv[]) {
    int encode = 1;
    int stream = 0;
    if (argc > 1) {
        std::string arg = argv[1]; // Первый аргумент командной строки
        if (arg == "-d") {
            encode = 0; // Режим декодирования
        } else if (arg == "-e") {
            encode = 1; // Режим кодирования
        } else if (arg == "-s") {
            stream = 1; // Потоковый режим
        }
        else {
            return 1; // Завершаемся с кодом не 0
        }
    }
    if (encode == 1) { // Кодирование
        if (stream == 1) { // Потоковое кодирование
            std::vector<std::uint8_t> buf;
            std::uint8_t bytes;
            while (std::cin.read(reinterpret_cast<char*>(&bytes), 1)) { // Считываем байты по одному
                buf.push_back(bytes);
                if (buf.size() == 4) { // Кодируем по 4 байта
                    std::cout << encode_bytes(buf); // Выводим результат
                    buf.clear();
                }
            }
            if (!buf.empty()) {
                buf.resize(4, 0); //  Дополняем нулями
                std::cout << encode_bytes(buf);
            }
            std::cout << "" << std::endl;
        } else { // Вся строка
            // создаём итератор ввода, который считывает ввод до конца
            std::vector<std::uint8_t> input_data((std::istreambuf_iterator<char>(std::cin)), std::istreambuf_iterator<char>());
            std::string encoded_data = ascii85_encode(input_data);
            std::cout << encoded_data << std::endl;
        }
    } else { // Декодирование
        try {
            // Считываем ввод до конца
            std::string encoded_data((std::istreambuf_iterator<char>(std::cin)), std::istreambuf_iterator<char>());
            std::vector<std::uint8_t> decoded_data = ascii85_decode(encoded_data);
            for (std::uint8_t bytes : decoded_data) { // Выводим данные
                std::cout.write(reinterpret_cast<const char*>(&bytes), 1);
            }
        } catch (const std::exception& e) { // Завершаемся с кодом не 0
            std::cerr << "Error: " << e.what() << std::endl;
            return 1;
        }
    }
    return 0;
}
