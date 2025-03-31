#include "ascii85.h"


// Кодирование 4 байт ASCII85
std::string encode_bytes(const std::vector<std::uint8_t>& bytes) {
    std::uint32_t val = 0;
    for (std::size_t i = 0; i < bytes.size(); ++i) {
        val = (val << 8) | bytes[i]; // Сдвигаем значение на 8 бит влево и добавляем текущий байт
    }
    if (val == 0 && bytes.size() == 4) {
        return "z";
    }
    std::string res;
    for (int i = 0; i < 5; ++i) {
        res = char(val % 85 + 33) + res; // Смещаем на значение "!"
        val /= 85;
    }
    return res;
}

// Кодирование ASCII85
std::string ascii85_encode(const std::vector<std::uint8_t>& data) {
    std::string res = "";
    for (std::size_t i = 0; i < data.size(); i += 4) {
        std::vector<std::uint8_t> bytes; // Храним 4 байта
        int num_bytes = 0;
        for (std::size_t j = 0; j < 4; ++j) {
            if (i + j < data.size()) { // Проверка на выход за пределы
                bytes.push_back(data[i + j]); // Заполняем байтами
                num_bytes++;
            } else {
                bytes.push_back(0); // Заполняем нулями
            }
        }
        std::string encoded_str = encode_bytes(bytes);
        if (num_bytes < 4) { // Удаляем лишние символы в конце строки
            num_bytes++;
            encoded_str = encoded_str.substr(0, num_bytes);
        }
        res += encoded_str;
    }
    return res;
}

// Декодирование 4 байт ASCII85 
std::vector<std::uint8_t> decode_bytes(const std::string& bytes) {
    if (bytes == "z") {
        return {0, 0, 0, 0};
    }
    std::uint32_t val = 0;
    for (char c : bytes) {
        val = (c - 33) + val * 85; // Сдвигаем на значение "!"
    }
    std::vector<std::uint8_t> res(4); // 4 байта на результат
    for (int i = 3; i >= 0; --i) {
        res[i] = (val & 0xFF); // Получаем результат используя битовую маску 
        val >>= 8; // Сдвигаем текущее значение на 8 бит вправо
    }
    return res;
}

// Декодирование ASCII85
std::vector<std::uint8_t> ascii85_decode(const std::string& encoded) {
    std::string data = encoded;
    std::vector<std::uint8_t> res;
    for (std::size_t i = 0; i < data.size(); i += 5) {
        std::string bytes = data.substr(i, 5); // Получаем подстроку из 5 символов
        while (bytes.length() < 5) {
            bytes += 'u'; // Дополняем строку до 5 символов последним символом ASCII85
        }
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

