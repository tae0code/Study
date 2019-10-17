# 4장 ; 강제변환
## 명시적과 암시적
먼저, 값의 타입을 변경하는 과정에서 명시적으로 바꾸면 **Type Casting**, 암시적이면 **강제변환** 이라고 하는데 이 책에서는 **명시적 강제변환** 과 **암시적 강제변환**에 대해 명백하면 명시적, 숨겨져있으면 암시적이라고 한다.

내가 이해한 바로는 **강제 변환을 할 때, 타입을 명확하게 지정을 해주면 명시적 강제변환, 타입을 컴파일러에서 자동변경 해주면 암시적 강제변환이라 생각한다.**

## 추상 연산
### 1. ToString 
문자열이 아닌 값을 문자열로 만들어주는 추상 연산 함수
그냥.. string화 시켜주는 함수이다.
> 일반 객체는 내부[[class]]를 반환한다는데 이에 대한 예를 모르겠다.
> var a = function(){};일 경우에도 ToString으로 출력해도 함수 자체를 String으로 만들어서 return 한다.
#### Json.stringify()
안전한 값은 모두 문자열화가 가능하다.
불안전한 값들 ( undefined, function, 순환참조 )들은 변환하면 undefined로 return해준다. 
만약 불안전한 값들이 배열속에 존재하면 null로 변경해서 해준다.
```javascript
var a = ['a',1,undefined,null,function(){}];
JSON.stringify(a); // result : "["a",1,null,null,null]"
```
> 테스트해보니 배열에 undefined와 null이 있을 경우, ToString은 값을 할당하지 않는다.
> ```javascript
> var a = ['a',1,undefined,null,function(){}];
> a.ToString(); // result : "["a",1,,,function(){}]"
> ```
또한 환영 참조(객체 안의 변수가 해당 객체를 참조하는 순환이 되는 경우)의 경우에는 해당 객체에 toJSON()이 있는지 먼저 확인 후, 만약 없다면 에러가 난다.
따라서, 불안전한 값이 존재할 경우, toJSON()이라는 함수를 정의해서 **안전한 값으로 변경해줘야 한다.**
JSON문자열로 바꾸는게 아닌, JSON문자열로 변경 가능한 **안전한 값**을 주는게 목표이다.

>추가적인 팁으로, JSON.stringify()는 인자를 총 3개 받을 수 있다.
>첫 번째 인자는 JSON형식으로 바꿀 객체
>두 번째 인자는 객체에서 포함 혹은 포함하지 않을 프로퍼티를 필터링하는 대체자
>세 번째 인자는 들여쓰기의 방법에 대한 인자
>해당 방법은 간단하므로 정리하지 않았다.

JSON.stringify()는 두 가지 특징을 가진다 생각하면 될 것 같다.
- JSON.stringify()는 ToString의 추상연산 규칙에 따른다.
- toJSON() 메서드가 있다면 toJSON()부터 호출되어 강제변환된다.

### 2. ToNumber
ToNumber()는 숫자가 아닌 값을 숫자로 만드는 추상 연산 함수
- true -> 1
- false -> 2
- undefined -> NaN
- null -> 0
- 기타 객체
	- 기타 객체에서는 valueOf()메서드가 있고, 해당 메서드가 원시 값을 반환하면 강제 변환한다. 혹은 toString()으로 강제변환한다.
	- 만약 어떻게든 원시 값으로 바꿀 수 없을 경우 TypeError가 발생한다.

### 3. ToBoolean
ToBoolean()은 true/false로 바꾸는 추상 연산 함수이다.
특이한 점은 Falsy값에 대해서만 false를 넘겨주는데, 그 이외에는 모두 true로 본다는 것이다.
- undefined
- null
- false
- +0, -0, NaN
- ""
위 데이터 이외에는 모두 true이다.

그렇다면 **Falsy** 는 뭘까?
몰라. 그냥 외워버려

결론 : 위 List가 Falsy값이고 그 이외는 다 Truthy니까 저거 외우면 됨

## 명시적 강제 변환
### 1. 문자열<-->숫자
문자열과 숫자의 강제변환은 String(), Number() 함수를 사용하고 앞에 new를 붙이지 않는다.
> new를 붙이면 객체 래퍼를 생성, 아니면 생성하지 않고 변환

또, 앞에서 언급한 ToString(), ToNumber()를 통해서도 명시적 강제 변환이 가능하다.

```javascript
var a = "3";
var b = 4;
String(b); // result : "4"
b.toString(); // result : "4"
Number(a); // result : 3
a.toNumber(); // result : 3
+a; // result : 3
-a; // result : -3
```
띠용.. +/-를 저렇게 사용할 수 있다는 걸 처음알았다.
단항연산자 +/-는 피 연산자를 숫자로 명시적 강제변환하는데 암묵적 강제변환인 줄 알았지만 명시적이라고 한다.(왜일까?)

근데 사용하는걸 지양한다고 나와있다.
```javascript
1 + - - - + + + - - 1; // result : 0
```
극단적인 경우이지만 저런 경우 해석이 난해하기 때문이다.

#### 날짜와 숫자의 변환
사실 Date 객체는 1970년 1월 1일 기준으로 현재까지의 시간을 초로 변환한 것을 가지고 있다. 
사실 new Date()를 하면 현재 날짜를 일련의 방식으로 return 해주지만 TimeStamp형식으로 보고 싶다면 new Date().getTime()을 사용한다.

TimeStamp형식으로 강제변환하는 방법은 메서드를 호출하는 방법이 아닌 위의 단항연산자를 사용해도 가져올 수 있다.
```javascript
var timestamp1 = +new Date();
var timestamp2 = new Date().getTime();
var timestamp3 = Date.now(); // 추천하는 방법
// 위의 결과는 동일하다
```
#### ~(틸드)
~x는 -(x+1)로 생각하면 된다. 
만약 -1을 return하는 메서드 앞에 틸트를 붙인다면 값은 0으로 나오고,
이외의 값을 return 하는 메서드 앞에 틸트를 붙인다면 값은 0이 아닌 수가 나올 것이다.

앞서 정리한 Boolean에 대한 형변환을 되새겨보자면, falsy한 값은 **false**, truthy한 값은 **true**로 변환을 하는데,
틸트의 특성인 **-1이 들어오면 0이 나온다.** 를 이용하여 불리언 값으로 적절하게 만들 수 있다.

또한 **~~(더블틸트)** 를 이용해서 비트를 잘라낼 수도 있는데, 소숫점을 잘라내는 용도로 사용할 수 있다. 이와 비슷한 문법으로 **|** 연산이 있지만, 우선순위에 사소한 문제가 있어 **~~** 를 사용하는게 더 유용하다.

### 2. 숫자 형태의 문자열 파싱

숫자 형태를 가진 문자열을 파싱하는 방법으로는 **parseInt**를 이용한다.
**parseInt**는 왼쪽부터 오른쪽으로 파싱을 진행하는데, 숫자가 아닌 것을 만나면 즉시 멈춘다.
```javascript
var a = "asb123";
var b = "123asdas";
parserInt(a); // result : NaN
parserInt(b); // result : 123
```
**parserInt** 는 문자열에 작동하고, 절대로 비 문자열 값을 인자로 주지 않는걸 추천한다. 

### 3. Boolean으로의 강제 변환
**Boolean**을 이용하여 모든 데이터를 Boolean 강제 변환이 가능하다.
하지만 **!!(이중부정)** 을 더 많이 사용한다.
실제로도 같은 결과 값을 내보이고 있다.

특히 많이 사용하는 3항 연산자에서는 Boolean의 강제 변환이 존재하는데
```javascript
var a = 1;
var b = a ? true : false;
```
위의 경우는 암시적 강제변환이 존재한다. 3항 연산자의 첫 번째 인자는 반드시 boolean으로 나와야하므로 암시적인 ToBoolean이 진행되는데, 이 코드보다는 아래의 코드를 사용하길 권장한다.

```javascript
var a = 1;
var b = !!a ? true : false;
```

## 암시적 변환
보기에 분명하지 않게 변형되는 타입변환은 모두 **암시적 변환**에 속한다.

### '암시적' 변환의 탄생 배경?
X라는 변수를 OO라는 타입으로 변경하기 위해서 PP라는 타입으로 변경한 후, 변환을 해줘야한다고 가정을 하면 코드는 아래와 같아질 것이다.
```javascript
OO tmp = OO(PP(X));
```
하지만 우리는 아래와 같이 간단하게 사용을 할 수 있다고 가정하자.
```javascript
OO tmp = OO(X);
```
그렇다면 중간에 PP로의 변환을 암시적으로 했다고 볼 수 있을 것이다.
더욱 간결해지고, 보기도 쉬워졌다.

겉만보면 단순하고 깔끔해지지만, 이에 대한 이해가 부족하고 아무곳이나 사용을 하게된다면 위험할 수 있다.
> 명시적이 좋다, 암시적이 좋다라는 것이 아니라 적절하게 사용하자는 의미이다.
### 문자열과 숫자의 암시적 강제 변환
**+** 연산자는 2가지의 의미로 Overload된다.
1. 숫자 간 덧셈
2. 문자열의 결합
```javascript
1+1; // result : 2
"1"+"1"; // result : "11"
[1,2]+[3,4]; // result : "1,23,4"
function a(){}+function b(){}; // result : NaN
```
결국은 숫자 및 Boolean이 아닌 데이터에 대해서는 String으로 변환 한 뒤, 문자열의 결합으로 Overload하여 연산된다.
>Boolean 타입에 대해서 true = 1 , false = 0 으로 생각해서 숫자 간 덧셈으로 연산된다.
 
#### 숫자->문자열
숫자를 문자열로 바꾸는 법에 대해서 가장 간단한 방법은 아래와 같다.
```javascript
13+""; // result : "13"
```
매우 간결해서 좋지만,  내부 로직을 좀 알아 볼 필요가 있다.
명시적 강제 변환인 String()과 암시적 강제 변환은 내부로직이 약간 다른데,
String()은 숫자를 문자열화 시킬 때 ToString() 메서드를 호출하고, 암시적 강제변환은 valueOf() 메서드를 호출한다.
```javascript
var a = {
	valueOf: function(){ console.log("valueOf"); },
	toString: function(){ console.log("toString"); }
};
a + ""; // result : "valueOf"
String(a); // result : "toString"
```
암시적 강제 변환이 되는 대상 데이터가 평범한 숫자가 아닌 객체라면 결과가 원했던 것이랑 다를 수 도 있다.

### Boolean 타입을 숫자로
간단하다.
**+** 연산자를 사용하면 된다.
```javascript
false+true+true; // result : 2
```

# 작성중 
