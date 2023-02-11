### МИНИСТЕРСТВО НАУКИ И ВЫСШЕГО ОБРАЗОВАНИЯ РОССИЙСКОЙ ФЕДЕРАЦИИ

### Федеральное государственное автономное образовательное учреждение высшего образования

## Дальневосточный федеральный университет
### ИНСТИТУТ МАТЕМАТИКИ И КОМПЬЮТЕРНЫХ ТЕХНОЛОГИЙ
### Департамент математического и компьютерного моделирования
### ДОКЛАД о практическом задании по дисциплине АИСД

# Эффективная длинная арифметика

### Жадик Кирилл Александрович, гр. Б9121-09.03.03пикд

### г. Владивосток, 2022

# Содержание

[*Содержание*](#содержание)

[*1. Введение*](#1-введение)

[*1.1 Длинная арифметика*](#1.1-длинная-арифметика)

[*1.2 Применение*](#1.2-применение)

[*1.3 Глоссарий*](#1.3-глоссарий)

[*2. Формальная постановка задачи*](#2-формальная-постановка-задачи)

[*3. Формальное описание и реализация алгоритма*](#3-формальное-описание-и-реализация-алгоритма)

[*3.1 Сложение длинных чисел*](#3.1-Сложение-длинных-чисел)

[*3.2 Вычитание длинных чисел*](#3.2-вычитание-длинных-чисел)

[*3.3 Умножение длинных чисел*](#3.3-Умножение-длинных-чисел)

[*3.4 Деление длинных чисел*](#3.4-Деление-длинных-чисел)

[*4. Тестирование*](#4.-Тестирование)

[*Список литературы*](#список-литературы)

# 1 Введение

## 1.1 Длинная арифметика
Длинная арифметика - это метод вычисления с представлением чисел в виде длинных последовательностей цифр, в том числе для вычисления больших чисел, которые не помещаются в стандартные представления чисел компьютера.

## 1.2 Применение

-	При решении олимпиадных задач.
-	В компьютерах низкой разрядности, микроконтроллерах.
-	Криптография.
-	Математическое и финансовое ПО, требующее, чтобы результат вычисления на компьютере совпал до последнего разряда с результатом вычисления на бумаге. В частности, калькулятор Windows (начиная с 95).
-	«Спортивные» вычисления знаменитых трансцендентных чисел ("число Пи", "число e" и т. д.) с высокой точностью.
-	Высококачественные изображения фракталов.


## 1.3 Глоссарий
1. База длинной арифметики - это максимальное число хранимое в массиве длинной арифметики(base)

2.  Комплексные числа — это числа вида $a + bi$, где $a$ и $b$ это обычные вещественные числа, а $i$ это так называемая мнимая единица: это число, для которого выполняется равенство $i^2 = -1$.

3. Разделяй и властвуй (англ. divide and conquer)  — парадигма разработки алгоритмов, заключающаяся в рекурсивном разбиении решаемой задачи на две или более подзадачи того же типа, но меньшего размера, и комбинировании их решений для получения ответа к исходной задаче

# 2. Формальная постановка задачи 


 В данной работе требуется реализовать алгоритмы длинного сложения, вычитания, умножения, деления наиболее эффективным способом.

# 3. Формальное описание и реализация алгоритма

## 3.1 Сложение длинных чисел
---
Для реализации сложения длинных чисел используем школьное сложение в столбик.
``` c++
vector<int> addition(vector<int> op1, vector<int> op2) {
    int lenop1 = op1.size();
    int lenop2 = op2.size();

    int dif = lenop1 - lenop2;

    for (int i = 0; i < dif; i++) {
        op2.insert(op2.begin(), 0);

    }
    for (int i = lenop1 - 1; i >= 0; i--) {
        if (op1[i] + op2[i] >= 10) {
            op1[i] = op1[i] + op2[i] - 10;
            op1[i - 1] += 1;
        } else {
            op1[i] = op1[i] + op2[i];
        }

    }
    return op1;
}
```
Эта функция реализует сложение двух больших целых чисел, хранящихся в виде векторов. Векторы представляют цифры целых чисел в обратном порядке. Программа сначала уравновешивает длины двух векторов, добавляя начальные нули к более короткому вектору. Затем он перебирает цифры справа налево, добавляя соответствующие цифры двух векторов и обрабатывая любой перенос. Наконец, он возвращает результат, который сохраняется в первом векторе и также в обратном порядке.


## 3.2 Вычитание длинных чисел
---
Вычитание реализуется аналогично сложению.

``` c++
vector<int> subtraction(vector<int> num1, vector<int> num2) {
    int lenop1 = num1.size();
    int lenop2 = num2.size();
    int dif = lenop1 - lenop2;
    for (int i = 0; i < dif; i++) {
        op2.insert(op2.begin(), 0);
    }
    for (int i = lenop1 - 1; i >= 0; i--) {
        if (num1[i] - num2[i] < 0) {
            num1[i] = num1[i] + 10 - num2[i];
            num1[i - 1] -= 1;
        } else {
            num1[i] = num1[i] - num2[i];
        }
    }
    return op1;
}
```
Сначала функция вычисляет разницу в длине между двумя массивами и добавляет нули в начало меньшего массива, чтобы сделать их равной длины. Затем функция выполняет поэлементное вычитание, начиная с последнего элемента массивов. Если результат вычитания отрицательный, функция добавляет к нему 10 и уменьшает следующий элемент на 1. Наконец, функция возвращает вычитаемый массив, который представляет результат вычитания.

## 3.3 Умножение длинных чисел
---
Для умножения длинных чисел использовался алгоритм быстрого преобразования Фурье (БПФ).
#### История алгоритма
По рассказам одного из авторов алгоритма, Джеймса Кули, всё началось в конце 1963 года. Джеймс Кули был нанят в IBM Thomas J. Watson Research Center в Yorktown Heights, что в Нью-Йорке. Кули работал над своим собственным проектом, когда к нему обратился Ричард Гарвин (Richard Garwin) и показал некоторые заметки Джона Тьюки (John Tukey) об алгоритме, который теоретически способен вычислять быстрое преобразование Фурье со скоростью, пропорциональной $N\log_2(N)$, а не $N^2$. Гарвин, в отличие от Кули, хорошо понимал всю важность этого алгоритма и его огромную практическую значимость, и поэтому настаивал на разработке этого алгоритма.

#### Основная цель

Основной задачей быстрого преобразования Фурье (FFT) является эффективное вычисление дискретного преобразования Фурье (DFT). С помощью этого можно умножать многочлены за время $O(nlogn)$.

#### Дискретное преобразование Фурье (ДПФ)

Пусть имеется многочлен n-ой степени:

$A(x) = a_0 x^0 + a_1 x^1 + \ldots + a_{n-1} x^{n-1}$

Из теории функций комплексного переменного известно, что комплексных корней n-ой степени из единицы существует ровно n. Обозначим эти корни через $w_{n,k}, k = 0 \ldots {n-1}$, тогда известно, что $w_{n,k} = e^{ i \frac{ 2 \pi k }{ n } }$. Кроме того, один из этих корней $w_n = w_{n,1} = e^{ i \frac{ 2 \pi }{ n } }$ (называемый главным значением корня n-ой степени из единицы) таков, что все остальные корни являются его степенями: $w_{n,k} = (w_n)^k$.

Тогда дискретным преобразованием Фурье (ДПФ) (discrete Fourier transform, DFT) многочлена $A(x)$ (или, что то же самое, ДПФ вектора его коэффициентов $(a_0, a_1, \dots, a_{n-1})$ называются значения этого многочлена в точках $x = w_{n,k}$

Аналогично определяется и обратное дискретное преобразование Фурье (InverseDFT). Обратное ДПФ для вектора значений многочлена $(y_0, y_1, \ldots y_{n-1})$ — это вектор коэффициентов многочлена $(a_0, a_1, \ldots, a_{n-1})$:

 ${\rm InverseDFT}(y_0, y_1, \ldots, y_{n-1})=(a_0,a_1...,a_{n-1})$

Разделим его на два многочлена, один — с чётными, а другой — с нечётными коэффициентами:

 $A_0(x) = a_0 x^0 + a_2 x^1 + \ldots + a_{n-2} x^{n/2-1}$
 $A_1(x) = a_1 x^0 + a_3 x^1 + \ldots + a_{n-1} x^{n/2-1}$
#### Быстрое преобразование Фурье

Быстрое преобразование Фурье (fast Fourier transform) — это метод, позволяющий вычислять ДПФ за время $O(n \log n)$. Этот метод основывается на свойствах комплексных корней из единицы (а именно, на том, что степени одних корней дают другие корни).

Основная идея БПФ заключается в разделении вектора коэффициентов на два вектора, рекурсивном вычислении ДПФ для них, и объединении результатов в одно БПФ.

Итак, пусть имеется многочлен $A(x)$ степени $n$, где $n$ — степень двойки, и $n>1$:

 $A_0(x) = a_0 x^0 + a_1 x^1 + \ldots + a_{n-1} x^{n-1}$
 $A_1(x) = a_1 x^0 + a_3 x^1 + \ldots + a_{n-1} x^{n-1}$

Нетрудно убедиться, что:
 $A(x) = A_0(x^2) + x A_1(x^2)$(1) 

Многочлены $A_0$ и $A_1$ имеют вдвое меньшую степень, чем многочлен $A$. Если мы сможем за линейное время по вычисленным ${\rm DFT}(A_0)$ и ${\rm DFT}(A_1)$ вычислить ${\rm DFT}(A)$, то мы и получим искомый алгоритм быстрого преобразования Фурье (т.к. это стандартная схема алгоритма "разделяй и властвуй", и для неё известна асимптотическая оценка $O(n \log n)$.

Итак, пусть мы имеем вычисленные вектора. Найдём выражения для $\{ y_k \}_{k=0}^{n-1} = {\rm DFT}(A)$.

Вспоминая (1), мы сразу получаем значения для первой половины коэффициентов:
 $y_k = y_k^0 + w_n^k y_k^1, ~~~~k = 0 \ldots n/2-1$

Итак, в результате мы получили формулы для вычисления всего вектора $\{ y_k \}$:
 $y_k = y_k^0 + w_n^k y_k^1, \ \ \ \ k = 0 \ldots n/2-1,$
 $y_{k+n/2} = y_k^0 - w_n^k y_k^1, \ \ \ \ k = 0 \ldots n/2-1$
#### Реализация

Рассмотрим простую рекурсивную реализацию БПФ и обратного БПФ, реализуем их в виде одной функции, поскольку различия между прямым и обратным БПФ минимальны. Для хранения комплексных чисел воспользуемся стандартным в C++ STL типом complex.
```c++
void fft(vector<ftype> &a, bool invert) {
    int n = (int) a.size();
    if (n == 1) return;

    vector<ftype> a0(n / 2), a1(n / 2);
    for (int i = 0, j = 0; i < n; i += 2, ++j) {
        a0[j] = a[i];
        a1[j] = a[i + 1];
    }
    fft(a0, invert);
    fft(a1, invert);

    double ang = 2 * pi / n * (invert ? -1 : 1);
    ftype w(1), wn(cos(ang), sin(ang));
    for (int i = 0; i < n / 2; ++i) {
        a[i] = a0[i] + w * a1[i];
        a[i + n / 2] = a0[i] - w * a1[i];
        if (invert)
            a[i] /= 2, a[i + n / 2] /= 2;
        w *= wn;
    }
}
```
В аргумент $\rm a$ функции передаётся входной вектор коэффициентов, в нём же и будет содержаться результат. Аргумент $\rm invert$ показывает, прямое или обратное ДПФ следует вычислить. Внутри функции сначала проверяется, что если длина вектора $\rm a$ равна единице, то ничего делать не надо - он сам и является ответом. Иначе вектор $\rm a$ разделяется на два вектора $\rm a0$ и $\rm a1$, для которых рекурсивно вычисляется ДПФ. Затем вычисляется величина $w_n$, и заводится переменная $w$, содержащая текущую степень $w_n$. Затем вычисляются элементы результирующего ДПФ по вышеописанным формулам.

Если указан флаг $\rm invert = true$, то $w_n$ заменяется на $w_n^{-1}$, а каждый элемент результата делится на 2 (учитывая, что эти деления на 2 произойдут в каждом уровне рекурсии, то в итоге как раз получится, что все элементы поделятся на $n$).

Тогда функция для перемножения двух многочленов будет выглядеть следующим образом:
```c++
void multiply(const vector<int> &a, const vector<int> &b, vector<int> &res) {
    vector<ftype> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    size_t n = 1;
    while (n < max(a.size(), b.size())) n <<= 1;
    n <<= 1;
    fa.resize(n), fb.resize(n);

    fft(fa, false), fft(fb, false);
    for (size_t i = 0; i < n; ++i)
        fa[i] *= fb[i];
    fft(fa, true);

    res.resize(n);
    for (size_t i = 0; i < n; ++i)
        res[i] = int(fa[i].real() + 0.5);
}
```
Эта функция работает с многочленами с целочисленными коэффициентами (хотя, понятно, теоретически ничто не мешает ей работать и с дробными коэффициентами). Однако здесь проявляется проблема большой погрешности при вычислении ДПФ: погрешность может оказаться значительной, поэтому округлять числа лучше самым надёжным способом — прибавлением 0.5 и последующим округлением вниз.

Функция для перемножения двух длинных чисел практически ничем не отличается от функции для перемножения многочленов. Единственная особенность — что после выполнения умножения чисел как многочлены их следует нормализовать, т.е. выполнить все переносы разрядов:
```c++
void normalize(vector<int> &a) {
    int carry = 0;
    for (size_t i = 0; i < a.size(); ++i) {
        a[i] += carry;
        carry = a[i] / 10;
        a[i] %= 10;
    }
}
```
### 3.4 Деление длинных чисел

Для начала необходимо реализовать функцю, которая будет сравнивать два числа.
```c++
bool compare(string num1, string num2) {
    if (num1.size() < num2.size()) return false;
    else if (num1.size() == num2.size() && num1 < num2) return false;
    return true;
}
```
Она будет возвращать $true$ если первое число больши или равно, чем второе, иначе $false$.

Опишим алгоритм деления
```c++
string division(string a, string b) {
    string reminder;
    ostringstream result;
    int count;
    if ("0" == b) {
        return "null";
    }
    a = delete_zeros(a);
    b = delete_zeros(b);
    if (!compare(a, b)) {
        return "0";
    }
    int len = a.size();
    for (int i = 0; i < len; i++) {
        count = 0;
        reminder.push_back(a[i]);
        while (compare(reminder, b)) {
            reminder = subForDivision(reminder, b);
            count++;
        }
        if (count != 0) result << count;
    }
    return result.str();
}
```
### 4. Тестирование
Основная цель тестирования - проверка корректности и эффективности операций длинной арифметики. Для проверки правильности ответов использовался язык программирования Python, так как операции длинной арифметики встроены в него по умолчанию.

###### Анализ операции сложения
Эксперментальное время линейное  - соответствует теоретической оценке $O(n)$

###### Анализ операции вычитания
Эксперментальное время линейное  - соответствует теоретической оценке $O(n)$

###### Алогоритм быстрого преобразования Фурье
<div>
    <div style="display: flex; justify-content: center">
        <img  src="Images\fft.png"/>
    </div>
    <p style="font-style: italic; text-align: center">Рисунок 3. График работы алгоритма БПФ</p>
</div>
Эксперементальное время соответствует теоретической оценке O(nlog n)

###### Анализ операции деления
Эксперментальное время линейное  - соответствует теоретической оценке $O(n)$

##### Общий анализ
Все тесты прошли корректно и полученное время соответсвует эксперементальной оценке операций.

# Список литературы
---
1.	https://brestprog.by/topics/longarithmetics/
2.	https://e-maxx.ru/algo/big_integer/
3.	https://habr.com/ru/post/172285/
4.	https://habr.com/ru/post/124258/ 
5.	https://wiki.fenix.help/matematika/algoritm-evklida 
6.	https://ru.wikibrief.org/wiki/Division_algorithm 
7.	https://www.stud24.ru/programming-computer/dlinnaya-arifmetika/22260-63531-page1.html
8.	http://comp-science.narod.ru/DL-AR/okulov.htm
9.	https://programforyou.ru/poleznoe/dlinnaya-arifmetika-kak-operirovat-chislami-ne-pomeshchayushchimisya-ni-v-odin-iz-chislovyh-tipov
10.	https://cppalgo.blogspot.com/2010/05/blog-post.html
11.	https://itnan.ru/post.php?c=1&p=578718
12.	https://habr.com/ru/company/otus/blog/449996/
13.	https://ru.wikipedia.org/wiki/Быстрое_преобразование_Фурье
14.	https://algorithmica.org/ru/fft
15.	https://algorithmica.org/ru/karatsuba
16.	https://translated.turbopages.org/proxy_u/en-ru.ru.36bc7c60-633f5d51-e01bf12c-74722d776562/https/en.wikipedia.org/wiki/The_Karatsuba_multiplication
17.	https://www.youtube.com/watch?v=m9yO12Zlb1g&ab_channel=КафедраБИС
18.	https://www.youtube.com/watch?v=21C5cfD6FOo&ab_channel=AGalilov
19.	https://www.youtube.com/watch?v=yL0I2g69EpM&ab_channel=PavelMavrin
20.	https://ru.wikipedia.org/wiki/Длинная_арифметика
21.	http://www.ccas.ru/personal/karatsuba/alg.htm
22.	https://neerc.ifmo.ru/wiki/index.php?title=Арифметика_чисел_в_b-ичной_системе_счисления_(Длинная_арифметика)
23.	https://orenstudent.ru/LongArifmAddSub.htm
24.	https://programforyou.ru/poleznoe/dlinnaya-arifmetika-kak-operirovat-chislami-ne-pomeshchayushchimisya-ni-v-odin-iz-chislovyh-tipov
25.	https://habr.com/ru/post/207754/
26.	https://e-maxx.ru/algo/fft_multiply
27.	https://codeforces.com/blog/entry/1244
