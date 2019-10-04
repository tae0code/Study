
# 2장 ;  Value

## 배열 

배열에는 어떤 타입이든 담을 수 있다.

    var a = [1, "2", [3]]
    
    
 배열의 크기 유동성을 가진다.

    var a = [];
    a.length; // 0
    a[0]; = 1;
    a.length; // 1
   
  이와 같이 배열의 index에 아무런 제한없이 접근이 가능하다. 하지만 주의할 점이 몇 가지 존재한다.
  

 1. 배열의 index에 제한 없이 접근이 가능하지만, 건너 뛰는 **구멍**이 생긴다.

```javascript
var a = []; 
a[1] = 1;
a[0]; // undefined 
a.length; // 2;
```
건너 뛴 부분은 undefined로 처리 되지만 undefined로 대입한 것과는 다르다.

2. index 값이 아닌 Key값/프로퍼티 값으로도 접근이 가능하다.
```javascript
var a = [];
a["test"] = 1;
a["test"]; // 1
a["10"] = 10;
a["10"]; // 10
a[10]; // 10
```
Key값을 String으로 넣었다고 해도, 10진수로 표현이 된다면, 10진수로 접근이 가능하다. 
책에서는 가능하면 Key값이나 프로퍼티 값으로 쓰지 말라는데 쓸 일이 없을 것 같다.

### 유사 배열 --> 유사 배열이 뭔지 모르겠다. 공부하자



## 문자열
JS에서는 불변과 가변값에 대한 이해가 필요할 것 같다.
먼저 말하자면 **문자열 == 불변값**이고 배열에 저장된 char들의 집합은 가변값이다.

```javascript
var a = "abc";
var b = ["a","b","c"];
a.join("-");//undefined
b.join("-");//a-b-c
a.reverse();//undefined
b.reverse();//["c","b","a"]
```
이와 같이 문자열은 배열이 가지고 있는 function을 대부분 사용하지 못하지만, 정말 필요하다면 아래와 같은 방법으로 사용가능하다고 한다.
```javascript
var a = "abc";
var b = Array.prototype.join.call(a,"-");
b; //a-b-c
```

반대로 배열을 문자열로 쓰고싶다면 **배열.join()** 을 쓰면 손쉽게 문자열로 바꿀 수 있다. 

## 숫자
음.. JS 숫자는 너무 복잡했다.

JS의 숫자는 정수, 부동 소숫점을 모두 포함하며, 심지어는 0과 inf에도 음,양수가 존재했다.

### 먼저 부동 소숫점과 정수를 알아보자
그냥 내가 이해한 바로는
**부동 소숫점은 소숫점 아래가 0이 아닌 수를 가진 숫자이다.**
**정수는 소숫점 아래가 0을 가진 숫자이다.** 
라고 이해했다.

그 이유는 간단하다. 소숫점 아래가 0이면 정수를 보여줬다.
```javascript
var a = 10.0;
a; // 10
a = 10.1;
a; // 10.1
```

큰 지수 숫자는 **1E3**과 같이 표현하였으며 2진,8진,16진수는 별 다른 내용이 없기에 넘어갔다.

### JS에서는 작은 숫자는 정확하지 않다.
이 part는 읽으면서 경험을 떠올릴 수 있었다.
0.3 == 0.1+0.2와 동일하다 생각하지만, JS는 0.3을 0.30000000...3으로 인식하기도 한다.(오차가 있다.)
따라서 **Number.EPSILON**이라는 매우 작은 값을 이용하면 된다. 
예를 들자면 **(0.3-(0.1+0.2))<Number.EPSILON**이면 동일하다 생각을 하는 것이다.

> 안전한 정수 범위 --> 필요할 때 읽으면 될 것 같다.

> 정수인지 확인하는 방법 : *Number.isInteger()* 을 이용하자.  


## 특수 값

> ### undefined
> 값을 정의하지 않았을 경우

> ### null
> 값이 있었는데 없앤경우(? 말이 이상하다)

> ### void연산자
> 뒤에 오는 피연산자의 return 값을 undefined로 만든다.
> 그렇다고 기능을 없애는 것은 아닌 것 같다.
> ```javascript
> var a = void setTimeout( console.log("void"),100); // result : void
> a; // result : undefined
> ```
>즉 실행은 하는데 그에 대한 return을 undefined로 만드는 것 같다.

> ### NaN
>  NaN, Not a Number-- 명칭은 숫자가 아닌 값이라고 한다.
>  하지만 명확히 말하자면 숫자로 표현이 불가능하거나, 숫자로 만드는 것을 실패한 경우이다.
>  ```javascript
>  var a = 2/"abc";
>  a; // result : NaN
>  typeof a; // result : number
>  typeof a==="number"; // result : true
>  ```
>  숫자를 string으로 나눈다면 어찌 표현할 길이 없기 때문에 NaN으로 정의한다.
>  근데 이상하게도 NaN은 number이라고 생각을 한다..
>  그리고 더 이상한 점은 NaN == NaN이 아니라는 점이다.
>  ```javascript
>  NaN === NaN // result : false
>  NaN == NaN // result : false
>  ```
>  Reflexive가 없다는 특징을 가지는데 몰라서 찾아봤다.
> 그냥 다른 모든 것들과 비교 했을 때 비교가 불가능하고, 심지어 자기 자신과 비교가 불가능 한 것 같다.
> NaN인지 아닌지 찾아주는 함수는 isNaN()이지만 ES5에서 적용하는 windows.isNaN()은 결함이 있다.
> ```javascript
> window.isNaN(NaN); // true
> window.isNaN("abc"); // true
> Number.isNaN(NaN); // true
> Number.isNaN("abc") // false
> ```
> string "abc"도 NaN으로 인식하는 멍청이기 때문에 Number.isNaN을 사용하자.


> ### Infinity
>  이 친구는 수학적으로 무한대가 나오는 경우 혹은 값이 너무나도 큰 경우 나옵니다.
>  근데 특이하게 - 부호가 붙는 경우가 있다.
>  ```javascript
>  1/0; // result : Infinity
>  -1/0; // result : -Infinity
>  ```

> ### 0
> 이 친구도 Infinity처럼 부호가 붙는다!
>  ```javascript
>  0/1; // result : 0
>  0/-1; // result : -0
>  ```
>  방향성을 보기 위해서는 좋은 것 같다.

> ### 동등 비교
> 특이한 성격의 값에 대해서는 Object.is()가 해답을 준다.
> 하지만 그게 아니라면 **===** 혹은 **==**을 사용하는 것을 권장한다.

## 값과 레퍼런스
자바스크립트에서는 포인터라는 개념이 없다는 것을 인지하고 있어야한다.
```javascript
var a = 1;
var b = a;
b++;
a; // 1
b; // 2
```
단순 값들은 값만 복사된다.

하지만 객체나 함수 같은 값들은 공유할 수 있게 전달된다.
```javascript
var a = [1,2,3];
var b = a;
b.push(4);
a; // [1,2,3,4]
b; // [1,2,3,4]
```
a와 b는 동일한 배열을 바라보고 있다.
즉, 공유가 된다는 뜻이다.  그냥 **바라보고** 있다.

```javascript
b = [1,2,5]
a; // [1,2,3,4]
b; // [1,2,5]
```
**바라보는 값**을 바꾸므로 a에는 전혀 지장을 주지 않는다.
함수의 인자로 넘기는 값도 이와 같은 원리로 작동한다.
만약 함수의 인자로 넘기는 값이 변경되지 않았으면 좋겠다면 **slice()**함수를 이용하자.
