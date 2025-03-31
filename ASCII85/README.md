# ASCII85
## Author
Коровин Данил Павлович, группа 24.Б81-мм
## Contacts
st128737@student.spbu.ru
## Description
```
ASCII85 encoder and decoder
$ ascii85    # читает байты из STDIN и выдаёт ASCII85 в STDOUT/
$ ascii85 -e # то же самое
$ ascii85 -s # потоковый ввод
$ ascii85 -d # читает ASCII85 из STDIN и выдаёт байты в STDOUT; при ощбке завершается с кодом, отличным от 0
```
## Build
```
chmod +x build.sh test.sh
./build.sh
```
## Run 
```
./test.sh
./ascii85 <test_encode.txt> output.txt
./ascii85 -e <test_encode.txt> output.txt
./ascii85 -s <test_encode.txt> output.txt
./ascii85 -d <test_decode.txt> output.txt
```
## Google Test
```
./ascii85_tests
```
## Python Test
```
python3 test.py
```


