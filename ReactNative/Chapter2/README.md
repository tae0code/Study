# Chapter2. 개발 환경 설정

## 2.1 맥 개발 환경 설정
나는 맥 유저이기 때문에 맥 개발 환경 설정만 체크하겠다.  
1. 노드(Node)  
2. 왓치맨(Watchman)  
3. Xcode 등을 설치해야한다.  

### 홈브루 설치
Homebrew는 맥용 패키지 관리자라고 생각하면된다.  
터미널에 아래의 명령어를 입력해보고, 설치가 안되어있다면 홈브루 사이트로 가서 설치를 해야한다.  
`brew --version`  

### 노드 설치
터미널을 열고 아래의 명령어를 실행하여 노드를 실행한다.  
`brew install node`

### 왓치맨 설치
Watchman은 특정 디렉토리의 파일에 변경이 발생하면 특정 동작을 하는 역할이다.  
소스 코드의 변경이 있으면 자동적으로 빌드하고, 시뮬레이터에 업로드를 하기위해서 왓치맨을 사용한다.  
`brew install watchman`  
`watchman --version // 정상 설치시, 버전 확인 가능`  

### 리액트 네이티브 CLI 설치
리액트 네이티브를 시작하는 방법은 Expo CLI와 리액트 네이티브 CLI가 있다.  
권장하는 사항은 리액트 네이티브 CLI이다.  

`npm install -g react-native-cli`  
`react-native --version // 정상 설치시, 버전확인 가능`  

### Xcode 설치
iOS 모바일 앱을 개발하기 위해서는 Xcode가 필요하다.  


### 코코아포드 설치
Cocoapods는 iOS개발에 사용되는 의존성 관리자이다.  
노드와 노드 패키자 관리자 관계랑 비슷하다.  
`sudo gem install cocoapods`  

### 자바 개발 킷 설치
안드로이드 개발을 위해서 설치하자.  
`brew tap AdoptOpenJDK/openjdk`  
`brew cask install adoptopenjdk8`  

### 안드로이드 스튜디오 설치
안드로이드 개발을 위해서 설치하자.  
> 안드로이드 스튜디오 검색해서 설치하면 된다.  

