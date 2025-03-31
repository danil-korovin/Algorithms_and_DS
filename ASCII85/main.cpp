#include "ascii85.h"


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
