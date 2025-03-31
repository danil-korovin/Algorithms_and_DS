import base64
import random
import os
import string
import subprocess


#Генерируем случайную строку.
def generate_random_string(length):
    characters = string.printable.replace('\n', '') # Убираем лишнее
    return ''.join(random.choice(characters) for _ in range(length))

#Кодируем строку с помощью base64
def python_base64_encode(data):
    return base64.a85encode(data.encode('utf-8')).decode('ascii')

def test_ascii85_with_python(input_text):
    #Записываем test_encoder.txt
    with open("test_encoder.txt", "w") as f:
        f.write(input_text)

    #Кодируем с помощью C++
    try:
        subprocess.run(["./ascii85", "-e"], check=True, stdin=open("test_encoder.txt", "r"), stdout=open("output.txt", "w"), text=True)
    except subprocess.CalledProcessError as e:
        print(f"Error running C++ encoder: {e}")
        return False

    #Читаем результат из output.txt
    with open("output.txt", "r") as f:
        cpp_encoded = f.read().strip()  

    #Кодируем с помощью Python
    python_encoded = python_base64_encode(input_text)

    #Сравниваем результаты кодирования
    if python_encoded == cpp_encoded:
        print(f"C++ = '{cpp_encoded}', Python = '{python_encoded}'")
        return True
    else:
        print(f"Encoding mismatch: C++ = '{cpp_encoded}', Python = '{python_encoded}'")
        return False


def main():
    num = 15  
    test_lengths = [random.randint(1, 100) for _ in range(num)] # Случайная длина строк
    passed = 1
    for i, length in enumerate(test_lengths):
        random_text = generate_random_string(length)
        print(f"Test {i + 1} (Length: {length})")
        if not test_ascii85_with_python(random_text):
            print(f"Test {i + 1} FAILED")
            passed = 0
        else:
            print(f"Test {i + 1} PASSED")

    # Удаляем временные файлы
    for filename in ["test_encoder.txt", "output.txt"]:
        if os.path.exists(filename):
            os.remove(filename)
            
    if passed == 1:
        print("All tests passed!")
        return 0
    else:
        print("Some tests failed.")
        return 1
    
           
if __name__ == "__main__":
    main()
