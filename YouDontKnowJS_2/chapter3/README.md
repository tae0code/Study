
# Chapter3; 함수 vs 블록 스코프

## 1. 함수 기반 스코프
```javascript
function foo(a){
   var b = 2;
   function bar(){
      ~
   }
   var c = 3;
}
```

함수 기반 스코프는 말 그대로, 함수가 만든 스코프이다.
Global Scope --> foo()
"foo" Scope --> a, b , bar(), c
foo() 함수가 만든 블록으로 인해 Scope가 생긴 것이다.
Global Scope는 a,b,c,bar()에 접근이 불가능하며 이는 foo 스코프에 종속되었다고 볼 수 있다.

## 2. 일반 스코프에 숨기
함수를 이용해서 코드를 숨기는 기법.
- 기존 코드에서 숨기고 싶은 코드를 함수로 감싸버린다.
- 애초에 함수 내부에 코드를 작성한다.

이 방식을 이용하는 이유는 **필요한 것만 내놓고 숨겨야 한다**라는 설계 원칙에서 나온다.
음.. 그냥 접근하지도 않는 애들을 구지 글로벌 스코프나 다른 스코프에 내놔야하는 것이냐는 것이다.

```javascript
function doSomething(a){
	b = a + doSomethingElse( a * 2 );
	console.log( b * 3 );
}

function doSomethingElse(a){
	reutnr a - 1;
}

var b;
doSomething(2); // 15
```
위 코드는 너무 불필요하게 많은 것을 공개해둔 상태이다. **doSomethingElse(), b** 는 구지 밖에 없어도 될 듯하다. 왜냐면 모두 doSomething()에서 접근하는 함수와 변수이기 때문이다.

이를 바꿔본다면 아래와 같다.
```javascript
function doSomething(a){
	function doSomethingElse(a){
		reutnr a - 1;
	}
	var b = a + doSomethingElse( a * 2 );	
	console.log( b * 3 );
}

doSomething(2); // 15
```
확실하게 doSomethingElse와 b는 외부로부터 영향을 받지 않고 doSomething에 종속되어 있음을 확인할 수 있다.

### 2-1 충돌 회피
충돌 회피란 같은 변수 혹은 함수명을 사용할 때, 다른 용도이지만 예기치 못하게 원치 않은 값을 받아오거나 넣는 경우를 피하는 것이다.

```javascript
function foo(){
	function bar(a){
		i=3;
		console.log(a+i);
	}
	for(var i=0; i<10; i++){
		bar(i*2);
	}
}
```
위의 코드는 무한 루프를 돌게 한다. 
bar()함수에 있는 ```i=3;```이 for문에 있는 i를 의도치 않게 변경 시키고 있기 때문이다.
이 때, bar 함수에 있는 i가 var로 변수선언을 하지 않았기에 외부 스코프에서 i를 찾는 것이다.

``` var i = 3; ```으로 변경하여 해결할 수 도 있지만, 애초에 변수 명을 바꿔서 ``` var j = 3; ```으로 사용하는게 더 좋은 선택지이다.

#### Global NameSpace에서 충돌
 글로벌 스코프에서는 개발자의 실수로 충돌이 많이 생기는 편이 아닌 것으로 알고 있다.(변수 중첩 등)
 책을 통해 새롭게 안 내용이지만 라이브러리로 인한 충돌이 많은 편이라고 한다.
 
따라서 라이브러리에는 고유 이름을 부여하여( 네임 스페이스라 칭한다. ) 해당 네임 스페이스의 속성으로 들어가 있는 라이브러리의 기능을 불러와서 사용한다고 한다.

#### 모듈관리 --> 2권에서 공부하자.

## 3. 스코프 역할을 하는 함수
앞서 언급한 함수 기반 스코프는 이름을 가진 함수를 만들어야하고, 해당 함수를 호출해야하는 번거로움이 존재한다.
따라서 함수 이름을 정하지 않고, 호출하는 로직이 없어도 되는 구문이 있다.

```javascript
var a = 2;
(function foo(){
	var a = 3;
	console.log(a); // 3 
	})();
	console.log(a); // 2
```

글로벌 스코프에서는 foo() 함수를 찾을 수 없다.
만약 이전 코드와 같이 했다면 글로벌 스코프에서는 foo를 찾을 수 있었을텐데!
이와 같은 식을 함수 표현식이라 한다.


### 3-1 익명 vs 기명
함수 표현식은 함수명을 생략할 수 있다.
```javascript
(function(){console.log("no name");})(); // no name
```

하지만 이름이 없으니 추적이 힘들고
스스로 재귀 호출을 하지 못한다. (현재는 가능, 곧 불가능)
또한 코드 분석시 어떤 기능을 하는지 알기 힘들다.

따라서 함수 표현식이라도 이름을 작성해주는게 좋다.
```javascript
(function IHAVENAME(){ console.log("IHAVENAME");})(); // IHAVENAME
```

### 3-2 함수 표현식 즉시 호출하기
함수를 ( ) 로 감싸면 함수 표현식, 이 뒤에 다시 ( )를 붙이면 즉시 호출이 된다.
이를 IIFE(Immediately, Invoked, Funciton, Expression)라고 하는데 보통 익명 함수 표현식에 흔하게 사용한다.



## 4. 스코프 역할을 하는 블록
```javascript
for (var i=0; i<10; i++){
	console.log(i);
}
var foo = true;
if(foo){
	var bar = foo * 2;
	console.log(bar);
}
```
블록 스코프를 지원하는 다른언어들은  i는 for문 안에만 존재하고, bar는 if문 안에만 존재한다. 
해당 블록이 스코프 역할을 하기 때문인데, 해당 블록 내에서만 쓰는 아이들을 외부에 구지 선언을 할 필요가 없기에 내부로 넣어두고 외부에서 사용되지 않도록 하는 것이다.

안타깝게도 js에는 블록 스코프를 지원하지 않는다. 하지만 방법은 존재한다.

### 4-1. with
with문 안에 생성된 객체는 바깥 스코프에 영향을 줄 수가 없다.

### 4-2. try/catch
catch문 안에 있는 변수는 외부에서 접근이 불가능하다.
```javascript
try{
	console.log("try");
}
catch(err){
	console.log(err); // ok
}
console.log(err); // error
```
### 4-3. let
let은 해당 블록에서만 사용되게끔 해주는 키워드이다.
var과 동일하게 변수를 선언하지만, 사용되는 위치를 지정해주는 셈이다.
```javascript
var foo = true;
if(foo){
	let bar = foo * 2;
	console.log(bar);
}
console.log(bar); // referenceError
```

**let은 해당 블록에만 붙인다?** 는 비명시적이다.
어떤 스코프에 속하는지 혼란이 올 수도 있기 때문이란다.(사실 모르겠다. let이 속한 블록을 찾기는 쉬울 듯 한데?)

따라서 한 번 더 블록을 만들어주면 명시적 블록 스코프 스타일이 된다.
```javascript
var foo = true;
if(foo){
	{
		let bar = foo * 2;
		console.log(bar);
	}
}
console.log(bar); // referenceError
```

뒤에 나올 내용이지만, let은 호이스팅 효과를 받지 않아서 해당  블록에만 존재할 수 있는 것이다.
다른 말로, let을 만나기 전까지는 해당 변수는 **존재하지 않는 상태** 인 것이다.

또한 위와 같이 만드는 블록은 메모리 회수에도 유용한데
정말로 큰 데이터를 가지는 변수를 선언한다고 생각을 하면, 해당 변수는 언제 회수될 지 모르는 상태이다. 
하지만 위와 같이 블록을 만들어 주고, let으로 선언을 해준다면 명확하게 메모리를 회수할 수 있다.
```javascript
//after
function a(data){
	//~~~
}
var BigData = {....}; // 언제 회수될까?
a(BigData);
//before
function a(data){
	//~~~
}
{
	let BigData = {....};
	a(BigData);
} // 메모리 회수 
```

let을 사용하므로써 블록 스코프를 지원하지 않는 JS에서 관리를 유용하게 해줄 수 있음을 알 수 있다.

### 4-4. const

const도 우리에게는 많이 익숙하다. 선언된 값은 수정이 불가능하다는 점은 명확하고, JS에서는 해당 블록에서만 존재한다는 특징을 지니고 있다.
```javascript
var foo = true;
if(foo){
	const bar = foo * 2;
	console.log(bar);
}
console.log(bar); // referenceError
```


## 5. 결론

JS의 Scope는 다른 언어와는 약간.. 아니 많이 다르다.
정식으로 블록 스코프를 지원하지 않기에 이를 해결할 수 있는 방법을 위에 정리를 했으며, 이를 통해 효율적인 메모리관리와 유지보수가 쉬운, 오류가 적은 코드를 만들 수 있을 것 같다.
