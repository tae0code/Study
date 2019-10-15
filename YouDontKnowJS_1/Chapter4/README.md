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

# 작성중 
