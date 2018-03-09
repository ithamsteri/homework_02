## Домашнее задание 02

[![Build Status](https://travis-ci.org/ithamsteri/homework_02.svg?branch=master)](https://travis-ci.org/ithamsteri/homework_02)

**Цель:** найти применение возможностям стандарта C++14

**Необходимо:**
* В приложенном к задании исходном файле необходимо заменить, где это возможно
  конструкции на аналогичные из стандарта C++14;
* Реализовать недостающий функционал;
* Результат опубликовать в своём репозитории на bintray;
* Выслать на адрес электронной почты название пакета содержащим исполняемый
  файл ip_filter;
* Выдержка из файла со списком адресов к задаче прилагается.

**Дополнительно:**
* Наличие тестов.

### Установка пакета

Для Ubuntu Trusty нужно сделать следующее:

```shell
echo "deb http://ppa.launchpad.net/ubuntu-toolchain-r/test/ubuntu trusty main" | sudo tee -a /etc/apt/sources.list
echo "deb http://hamsterisoft.bintray.com/apt-repo trusty main" | sudo tee -a /etc/apt/sources.list
sudo apt-key adv --keyserver keyserver.ubuntu.com --recv-keys 1E9377A2BA9EF27F
sudo apt-key adv --keyserver keyserver.ubuntu.com --recv-keys 379CE192D401AB61
sudo apt-get update && sudo apt-get install libstdc++6 ip_filter
```

И можно пользоваться:

```shell
cat datafile.tsv | ip_filter | md5sum
```

### Генерация сборки

Запустить в корневом каталоге проекта

```shell
cmake -H. -BBuild
```

### Сборка проекта

Запустить в каталоге Build

```shell
cmake --build .
```

### Запуск тестов

Запустить в каталоге Build

```shell
ctest -V
```

### Запуск теста производительности

![bench result](https://github.com/ithamsteri/homework_02/raw/master/bench.png
"Benchmark results")

Для компиляции тестов производительности нужно установить
[Google Benchmark](https://github.com/google/benchmark) библиотеку. Опция
сборки тестов производительности по-умолчанию включена. Если CMake не найдет
библиотеку Google Benchmark, то тогда тесты производительности не будут собраны
и запущены.

Тесты производительности запускаются совместно с модульными тестами командой:

```shell
ctest -V
```

