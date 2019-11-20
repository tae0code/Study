# Chapter 5; 스코프 클로저

## 1. 깨달음
**"아, 클로저는 내 코드 전반에서 이미 일어나고 있었구나! 이제 난 클로저를 볼 수 있어!"**


## 2. 핵심
앞의 내용은 모두 자르고 핵심을 말해보겠다.
일단 아래의 코드를 살펴보자.

```javascript
function foo(){
	var a = 2;
	function bar(){
		console.log(a);
	}
	return bar;
}
var baz = foo();
baz(); // 2
```
앞의 내용을 제대로 이해했다면 bar()가 foo()의 렉시컬 스코프에 접근할 수 있다는 것을 알 수 있을 것이다.
여기서 핵심은 **baz라는 변수를 통해서 bar()함수를 호출했다.** 라는 것인데
눈으로 봤을 때도 baz와 bar의 스코프는 명확하게 다르다.
bar의 렉스컬 스코프는 foo() 함수 블록이고 baz의 렉시컬 스코프는 global이기 때문이다.

근데, 함수 foo()가 실행되고 내부의 스코프가 가비지 컬렉터로 정리되지 않았을까? 만약 foo 내부의 어떤 것이 사용 중이라면 아직 가비지 컬렉터는 메모리 정리를 하지 않았을 것이다.

baz가 실행되니까, 아직 메모리 정리가 되지 않았을텐데.. 그러면 누가 사용 중인 것일까?
바로 bar() 자신이 사용중인 것이다.
> 명확히 말하자면 참조 당했기 때문이다.

bar()는 foo()의 렉시컬 스코프 클로저를 가지고 foo는 bar가 나중에 참조할 수 있도록 스코프를 살려둔다.

baz를 통해서 bar는 살아 있으며, bar는 foo의 렉시컬 스코프 클로저를 가지고 있기 때문에 a에 접근이 가능한 것이다.

함수는 완벽하게 원래의 렉시컬 스코프를 벗어나서 실행 되었지만, **클로저**의 영향 덕분에 해당 렉시컬 스코프에 계속 접근이 가능한 것이다.
어떤 방식이든 다른 위치에서 ( 다른 말로 하자면 서로 다른 렉시컬 스코프에서 ) 접근할 수 있도록 해주는 것이 클로저의 역할이다.

```javascript
function foo(){
	var a = 2;
	function baz(){
		console.log(a);
	}
	bar(baz);
}
function bar(fn){
	fn();
}
```
위의 코드 또한 클로저의 영향을 받아서 bar함수에 baz함수를 fn으로 넘겨 실행을 시킬 수 있다.

## 3. 나는 이제 볼 수 있다.
```javascript
function wait(message){
	setTimeout(function timer(){
		console.log(message);
	},1000);
}
wait("Hello");
```
내부 함수 timer를 setTimeout의 인자로 전달했고, wait의 렉시컬 스코프 내부에 있으므로 message변수에 접근이 가능할 것이다.
wait함수를 실행 한 후, 1초 뒤에는 wait 내부의 스코프가 사라져야하지만 그렇지 않다.

엔진 내부에 setTimeout()에 참조가 존재하여 timer를 호출하므로 앞서 언급한 내용과 똑같이 스코프를 유지시킨다.

>jQuery에 대한 내용은 생략하겠다.

IIFE는 클로저의 예라고 하지만 단순한 IIFE는 클로저의 사례로 들 수 없다.
```javascript
var a = 2;
(function IIFE(){
	console.log(a);
})();
```
위 IIFE는 단순히 렉시컬 스코프 검색으로 a를 참조했을 뿐, IIFE가 해당 스코프 외각에서 호출된 적이 없기 때문이다.

하지만 클로저와 연관이 깊으니 코드를 잘 짜면 될 것 같다.
> 가장 어려운걸 가장 쉽게 말하다닛..

## 4. 반복문과 클로저


클로저를 설명하기에는 반복문이 딱이다.
```javascript
for(var i=1; i<=5; i++){
	setTimeout(function timer(){
		console.log(i);
	}, 1000);
}
```
이 코드를 짤 때는 1,2,3,4,5가 나오길 원했을 것이다.
불행하게도 이 결과는 6 6 6 6 6이 출력된다.
setTimeout함수는 콜백함수로 1초 후에 실행이 된다. 근데 그 사이 for문이 돌아버리기 때문에
i는 6이 되어버리고, setTimeout은 i를 참조하면서 6을 그대로 출력해버리기 때문이다.

이 문제를 해결하기 위해서는 setTimeout이 i를 잡아둬야하는 것인데..
자신만의 스코프에 저장을 해버리면 해결이 된다!
```javascript
for(var i=1; i<=5; i++){
	(function(){
		var j = i;
		setTimeout(function timer(){
			console.log(j);
		}, 1000);
	})();
}
```
원하는 값이 출력된다.
IIFE의 특성인 **바로 실행&스코프 생성** 덕분에  출력하고 싶은 값을 자기 스코프에 저장할 수 있게 되었다.

### 4-1 다시 보는 블록 스코프
이 문제를 간단하게 해결하는 방법은 앞서 배운 블록 스코프에 힌트가 있다.
바로 **let** 변수이다.
아래와 같이 코드를 작성하면 let의 특성을 이용하여 원하는 출력을 얻을 수 있다.
```javascript
for(let i=1; i<=5; i++){
	setTimeout(function timer(){
		console.log(i);
	},1000);
}
```

## 5. 모듈
간단하게 말하면 함수들을 모아놓은 API 같은 역할이다.
다만 내부 데이터는 비공개처리가 되어있다는 점이 중요하다.
> 이는 클로저를 이용한 것이다.

```javascript
function Module(){
	var a = 1;
	var b = 2;
	function PrintA(){
		console.log(a);
	}
	function PrintB(){
		console.log(b);
	}
	return{
		PrintA : PrintA,
		PrintB : PrintB
	};
}
var foo = Module();
foo.PrintA(); // 1
foo.PrintB(); // 2
```

PrintA, PrintB를 사용하려면 반드시 Module() 함수를 한 번이라도 호출해야한다.
최외각 함수가 실행되어야지 내부 함수가 해당 스코프 내에 존재하기 때문이다. 실행되지 않으면 스코프 자체가 없기에 접근이 불가능 하다.
또한, return으로 넘어온 객체에 대한 접근 권한은 있지만 이외의 데이터에는 접근할 수가 없다!

이 모듈 패턴을 이용하기 위해서는 두 가지 조건이 필요하다.
1. 내부 함수를 감싸는 최외각 함수가 존재해야 하고, 최소한 1회의 실행이 있어야 한다.
2. 최외각 함수는 최소 한 번은 사용할 내부 함수를 반환해야한다. 그 이유는 위에 설명한 내용에 있다.

이를 응용해, 하나의 인스턴스를 만드는 싱글톤 모듈도 만들 수 있다. 이는 함수 표현식으로 작성하면 된다.
```javascript
//singleton pattern
var foo = (function Module(){
	var a = 1;
	var b = 2;
	function PrintA(){
		console.log(a);
	}
	function PrintB(){
		console.log(b);
	}
	return{
		PrintA : PrintA,
		PrintB : PrintB
	};
})();
foo.PrintA(); // 1
foo.PrintB(); // 2
```

> 현재의 모듈, 미래의 모듈
> 추후에.. JS를 개발 할 때 뒤적이겠다.
> 지금 읽어도 와닿지 않는다.



