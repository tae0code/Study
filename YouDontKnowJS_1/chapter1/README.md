# Chapter1. 타입
---

## 1. JavaScript에서의 타입
동적 언어는 Type 개념이 없는 것이 아니라 **많은 의미를 내포하고 있다.**

총 7개의 내장 타입이 존재 한다. Primitives Type이라고 불리는데 Object는 예외이다.
- null
- undefined
- boolean
- number
- string
- object
- symbol(ES6부터 추가. 다른 chapter에서 소개)

> typeof 연산자의 결과
~~~javascript
typeof undefined === "undefined"; // result : true
typeof true === "boolean"; // result : true
typeof 1 === "number"; // result : true
typeof "1" === "string"; // result : true
typeof { life : 1 } === "object"; // result : true
typeof Symbol() === "symbol"; // result : true
typeof null === "object"; // result : true
typeof function a(){ /*something*/ } === "function"; // result : true
~~~

위 typeof 결과를 봤을 때, null은 Primitives Type이라고 했는데 Object라고 나온다.
null자체가 유일한 Primitives Type이지만 타입은 Object인 존재라 설명하고 있다.

그렇다면 null이라는 것을 null이라고 판단하기 위해서는 어떻게 해야할까?
~~~javascript
var a = null;
(!a && typeof a === "object"); // result : true
var a = { life : 1 };
(!a && typeof a === "object"); // result : false
~~~
위와 같이 null이 아닌 Object 객체에 대한 판단을 할 수 있다.

>> 추가적으로 배열도 Object로 분류된다. 다만 function은 typeof로 function으로 반환되는데 
>> 사실 function 자체는 Object의 하위타입이다.


## 2. 값은 타입을 가진다.

- 값은 타입이 있다. but 변수는 타입이 강제되지 않는다.
- 값이 없는(undefined)와 선언되지 않은(unclared)는 다른 개념이다.
  - unclared는 접근 가능 Scope내에 선언되지 않은 것을 의미한다.
  - 하지만 undefined 상태의 변수와 unclared 상태의 변수를 typeof로 보면 undefined로 뜬다.
  - 책에서 오타가 있다. 선언되지 않은을 undefined로 적어뒀다.
### 2.1 선언되지 않은 변수 (unclared) 를 Check하기 위한 방법
1. typeof를 사용한다.
~~~javascript
if(a){/*something*/} // referenceError 
if(typeof a !== "undefined"){/*something*/} // Success
~~~
2. 전역 변수는 모두 전역 객체의 property라는 점을 이용 --> window 객체를 이용하지 않는다면 사용하기 어렵다.(Node.js)
~~~javascript
if(window.a){/*something*/} // Success : a가 있다면
if(!window.a){/*something*/} // Success : a가 없다면
~~~

위의 방식이 통하지 않는 경우가 있다고 한다.
책에서는 Copy and Paste를 할 때 종종 발생한다고 적혀있다.
~~~javascript
var a = typeof Func1 !== "undefined" ? Func1 : function(){/*something*/};
~~~
이렇게 찾는 변수가 없을 경우, 직접 구현하게끔 유도한다.

의존성 주입 설계 패턴이라고 설명하는 코드가 있다.
~~~javascript
function do(Func1){
  var a = Func1 || function(){/*something*/};
}
~~~
do() 함수에 명시적으로 찾는 변수를 적어 놓는 것이 의존 관계를 전달하는 것인가?
명확하게 의존성 주입 설계 패턴이 뭔지 모르겠다.

**하여튼 typeof를 통해서 선언되지 않은 변수를 적절하게 처리할 수 있다.**

따로 정리하기는 올리지 않을 예정이다.


