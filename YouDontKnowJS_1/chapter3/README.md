# 3장 ; Natives

## 네이티브의 정의
네이티브는 환경에 종속되지 않는 내장 객체(함수)를 의미한다.
- String()
- Number()
- Boolean()
- Array()
- Object()
- Function()
- RegExp()
- Date()
- Error()
- Symbol()

신기한 것은 네이티브를 생성자처럼 이용하면 내가 원하는 결과가 안나온다.
```javascript
var a = new String("a");
typeof a; // result : object
a instanceof String; // result : true
a instanceof object; // result : true
a; // String{"a"} < 이 결과는 브라우저마다 다를 수 있다.
```
new String("a")를 했을 때, 원시 값 "a"를 다시 감싸버린 객체가 되버리는 것이다.

## 내부 Class
typeof가 'object'인 값은 **[[class]]** 라는 내부 프로퍼티가 있다. **[[class]]** 는 객체가 어떤 타입인지를 나타낸다.
해당 프로퍼티는 **Object.prototype.toString()** 으로만 직접적인 접근이 가능하다.

이를 통해 원시값에 대한 내부[[class]]가 있는지 확인이 가능하다.
```javascript
Object.prototype.toString("ab"); // result : object String
```
**원시 값이 내부[[class]]를 가지는게 아니라, JS에서 원시값을 자동으로 Boxing을 해주는 것이기에 위와 같은 결과가 나오는 것이다.**

## 그렇다면 자동으로 Boxing을 해주면 이점이 무엇일까?
원시 값에는 프로퍼티 혹은 Method가 없기에 네이티브로 Boxing을 해줘야한다. 
이를 JS가 자동으로 해주기 때문에 개발자는 **new String("abc");** 와 같은 코드를 작성하지 말고, **"abc"** 로 간결하게 작성하자.

> 그래도 어쩔 수 없이 수동으로 Boxing을 하는 경우가 있으므로 알아두면 좋을 것 같다.
> > 추가로 Boolean으로 Boxing을 하면, 해당 값은 "truthy"라고 나온다. 이 책에는 구지 Boxing을 수동으로 해야겠다면 **new Object** 를 사용하라고 권장한다.

## Unboxing
언박싱은 간단하다.
**valueOf()** 메서드를 통해서 값을 가져올 수 있다.
> String 객체의 원시값은 아래와 같이 **""** 을 이용해 쉽게 가져올 수 있다.
>  ```javascript
>  var a = new String("a");
>  var b = a + "";
>  b; // result : "a"
>  ```

## Array 생성자
Array를 만들기 위해서 2가지 방법이 있다.
1. var a = new Array(1,2,3);
2. var a =[1,2,3];
위 방법은 모두 동일한 결과를 보여준다. 

근데 약간 버그(?)가 존재하는데
```javascript
var a = new Array(3);
a; //result : [empty * 3] or [undefined * 3]
```
분명 3이란 수를 Array로 만들고 싶었는데, 빈 공간 3개나 만들어 버렸다!
심지어 저 **undefined** 는 우리가 알고있는 undefined가 아닌 '빈 공간'이라는 뜻이다!

따라서 배열을 만들고 싶다면, 
**var a = [1,2,3];** 이 방법을 사용하는 것이 가장 좋고,
난 값이 없으면 좋겠어! 라고 한다면
**var a = Array.apply(null,{length:3});** 이렇게 사용하는 것이 좋을 것이다.

## Object, Function, RegExp 생성자
이들 또한 선택사항이지만, 사용하지 않는 편이 좋다고 한다.
특히, Function과 RegExp는 생성자로 생성하지 는 것을 적극 추천한다.

## Date, Error 생성자
다른 생성자와 달리, Date, Error 생성자는 리터럴 형식이 존재하지 않기에 매우 유용하게 사용한다.
```javascript
//Date
var a = new Date(); // Date객체 생성
a; // 매우 잘 정리된 시간으로 나타내줌.
a.getTime(); // 1970년 1월1일부터 현재까지 흐른 시간(초)
//Error
throw new Error("직장인입니다."); //보통은 throw를 같이 쓴다.
```

## Symbol()
아직까지도 잘 이해가 안된다.
객체의 프로퍼티로 사용 가능하고, 충돌의 가능성이 없으며 유일한 값을 지닌 것이 **Symbol** 이라고 한다.
```javascript
var sym = Symbol("my symbol");
var a = {};
a[sym] = "symbol";
a; // {Symbol(my symbol): "symbol"}
```
... 공부가 필요하다. 어떻게 활용할 건지, 어떻게 해야 잘 쓸 수 있을 지 고민 좀 해봐야겠다.


# 정리
- JS는 원시 값을 감싸는 네이티브가 존재한다.
- 해당 네이티브에는 각 타입 별 유용한 메서드가 존재한다.(prototype에 정의되어 있다.)
- JS는 박싱을 자동으로 해주는 매우 똑똑한 아이다.
