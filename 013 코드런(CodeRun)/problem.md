# 문제

몇 개의 함수로 구성된 코드가 있다. 이 코드는 C/C++와 같이 main( )에서 시작된다. 그리고 각 함수는 중간 중간에 다른 함수를 호출한다. 우리는 이 코드에서 각 함수별 수행문(statements)이 실행되는 순서를 추적하고자 한다.  
main( )을 포함한 모든 함수는 이름과 함수의 내용으로 구성되어 있다. 함수 내용은 개별 수행문(statements)과 그 내부에서 다른 함수를 호출(call)하는 함수 호출(function call)의 순서(sequence)로 표현되어 있다. 모든 함수 이름은 영문 대문자 1글자이며, 수행문은 소문자 또는 숫자로만 구성된 문자열(string)로 표시되어 있다. 만일 어떤 함수의 수행 중에 다른 함수를 호출하는 경우, 이 호출은 해당 함수의 이름, 즉 영문 대문자 한 글자로 표시된다. 그리고 각 함수의 끝은 문자 ‘$’로 표시되어 있으며 이 문자를 만나면 함수는 자동 return되고 해당 Call은 종료된다. 아래는 4개의 함수 M, G, K, W로 구성된 프로그램의 예이다.

| 이름 | 내용                                |
| ---- | ----------------------------------- |
| M()  | i k pop push G bab ko mong K viva $ |
| G()  | so good bad K baby you W mart $     |
| K()  | killing me W W nice day $           |
| W()  | data struct kills every body $      |

시작은 항상 M(Main) 함수로부터 시작한다. 각 함수에서 개별 문장이 수행(execution)한 단위 동작은 그 문장이 포함된 함수 이름(function name)과 단의 문장을 ‘-’(minus) 기호로 연결한 문자열로 표시된다. 예를 들어 함수 F에서 수행한 문장이 act라면 'F-act'로 표현한다. 위에서 프로그램과 같이 4개의 함수 {M, G, K, W}로 구성되어 있다면 이 코드의 수행 순서는 다음과 표현된다.

```
M-i
M-k
M-pop
M-push
G-so
G-good
G-bad
K-killing
K-me
W-data
W-struct
W-kills
W-every
W-body
W-data
(..중략..)
W-body
K-nice
K-day
G-baby
G-you
W-data
(..중략..)
W-body
G-mart
M-bab
M-ko
M-mong
K-killing
K-me
W-data
(..중략..)
W-body
W-data
(...)
W-body
K-nice
K-day
M-viva
$END$
```

여러분에게는 전체 프로그램과 함께 어떤 순서를 나타내는 두 개의 정수 가 주어진다. 여러분은 이 프로그램이 수행될 때 k1, k2 번째에 해당하는 2개의 수행문을 앞서 설명한 함수-문장(ex., 'F-act')방식으로 출력해야 한다.  
만일 해당 순서에 대응하는 수행문이 없을 경우에는 문자열 ‘NONE’을 출력한다. 예를 들어 전체 나열된 수행문의 수가 100이고 k1 k2 이 각각 150, 200이라면 이 순차에 대응하는 수행문은 존재하지 않으므로 ‘NONE’을 출력해야 한다. 또 무한루프(infinite loop)로 인하여 코드가 종료되지 않으면 'DEADLOCK‘을 출력해야 한다. 예를 들어 아래 예제의 4번과 같이 recursive call로 인하여 종료되지 못하게 된다. 이 문제에서 recursive function의 종결조건은 따로 없다고 가정한다. 따라서 어떤 함수에서 call을 하여 다시 그 과정에 해당 함수가 호출되면 infinite recursion이 발생하므로 deadlock을 출력해야 한다. 이런 경우에는 DEADLOCK 문자열 하나만 출력한다.

# 입출력

입력파일 stdin 첫 줄에 3 정수 N k1 k2가 주어진다. N(2<= N <= 20)은 함수의 개수이다. 이어지는 N개의 줄에는 각 함수가 제시된다. 각 줄의 첫 항목은 함수의 이름(대문자 1자)이며, 이어서 함수의 수행 문장이 문자열로 해당 줄에 제시된다. 그리고 함수의 끝은 문자 ’$‘로 표시되어 있다. 개별 문장은 모두 소문자와 숫자로만 구성된 문자열이다. 함수 당 문장은 2개 이상 최대 30개까지 포함되어 있다. 단 호출된 함수는 항상 정의되어있다고 가정한다. 여러분은 k1, k2 번째에 수행된 함수-문장을 2개의 줄에 각각 하나의 문자열로 출력해야 한다. 또는 특별한 경우에는 NONE이나 DEADLOCK을 출력해야 한다.

## stdin1

```
4 4 7
M b W k S d w $
S ee ww G ss $
W k G q a $
G 88 99 $
```

## stdout1

```
G-99
M-k
```

## stdin2

```
4 4 6
M b W k S d w $
S ee ww G ss $
W k G q a $
G 88 99 $
```

## stdout2

```
G-99
W-a
```

## stdin3

```
4 8 70
M b W k S d w $
S ee ww G ss $
W k G q a $
G 88 99 $
```

## stdout3

```
S-ee
NONE
```

## stdin4

```
4 2 26
M b W k S d w $
S ee W ww G ss $
W k G q a $
G 88 99 S $
```

## stdout4

```
DEADLOCK
```
