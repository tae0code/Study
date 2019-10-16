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

# 작성중 
