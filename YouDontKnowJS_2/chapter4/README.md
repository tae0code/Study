# Chapter 5; 호이스팅

## 1. 닭이 먼저냐 달걀이 먼저냐
아래의 코드를 보자.
```javascript
//1.
a = 2;
var a;
console.log(a);
```
```javascript
//2.
console.log(a);
var a= 2;
```
다른 언어를 접한 사람들이라면 이해하기 어려울 코드이다.
첫 번째 코드는 2가 출력 되며 두 번째 코드는 undefined가 출력된다.

이유가 뭘까?

## 2. 컴파일러는 두 번 공격한다.
위의 코드를 이해하려면 1장의 컴파일러 부분을 다시 들여다보면 된다.
가장 먼저 컴파일러는 선언문과 대입문을 찾을 것이다.
1번 코드는
```
a = 2;
var a;
```
의 구문이 존재하는데, **JS는 선언문을 위로 끌어올리는 Hoisting(호이스팅)이 존재한다!**
따라서 
```
var a;
a = 2;
console.log(a);
```
가 실행되는 것이다.
이 때 중요한 것은 **선언문만 위로 올라간다** 라는 것인데

2번 코드는 이와 같은 맥락으로
```
var a;
console.log(a);
a = 2;
```
로 진행되기 때문에 undefined라는 결과가 나오는 것이다.

그렇다면 함수는 어떻게 될까?
```javascript
foo();
function foo(){
	console.log(a);
	var a = 2;
}
```
함수 또한 선언이기 때문에 가장 위로 올려보낸다!
foo()함수 내에 있는 ``` var a = 2; ``` 또한 함수 스코프 내에 있기에, 해당 스코프의 가장 상단으로 이동한다.
```javascipt
function foo(){
	var a;
	console.log(a);
	a = 2;
}
foo();
```

함수 또한 호이스팅 효과를 받지만, 함수 표현식은 **대입**이기 때문에 호이스팅 효과를 받지 못한다.
```javascript
foo();
var foo = function bar(){
	~~
}
```
를 호이스팅 적용한다면
```javascript
var foo;
foo();
foo = function bar(){
	~~
}
```
이 처럼 대입연산이기 때문에 호이스팅 효과를 받지 못한다.
또한 함수 표현식이 이름을 가지고 있어도, 해당 스코프에서 확인 할 수가 없다!

```javascript
foo(); // TypeError
bar(); // ReferenceError
var foo = function bar(){
}
```

## 3. 함수가 먼저다.
호이스팅의 우선 순위는 함수>변수 이다
따라서 함수와 변수명을 중복으로 가져가는 것은 매우 위험한데,
예제로 많은 코드가 있지만 한 가지만 보이겠다.

```javascript
foo(); // b
var a = true;
if(a){
	function foo(){ console.log("a"); }
}
else{
	function foo(){ console.log("b"); }
}
```
호이스팅이 적용된 코드를 보면
```javascript
function foo() { console.log("a"); }
function foo() { console.log("b"); }
var a;
foo();
a = true;
..
..
..
```
즉, b를 출력하는 foo 함수가 나중에 덮어 씌워지면서 결과는 b가 나온다.
만약 var a가 아닌 var foo 였다면 true가 나왔을 것이다.

## 4. 결과
호이스팅을 이해 못하면 JS에서 많은 오류를 범할 수 있음을 알 수 있었다. 
기존 다른 언어와 다른 매커니즘을 가지고 있음을 인지하고 코드를 작성하면 좋을 것 같다.
