# Chapter3; react-native 입문

리액트 네이티브 CLI를 이용하여 리액트 네이트브 앱을 만들어보자.  

## 1) 리액트 네이티브 프로젝트 생성
보통 리액트 네이티브는 업데이트가 어마어마하게 빠르게 이루어지기 때문에 호환성 문제가 발생할 수 있다.  
따라서 프로젝트 시작전에 리액트 네이티브의 버전을 fix시킬 필요가 있는데 터미널에서 아래의 명령어를 입력해 버전을 고정시켜주자.  
`npm config set save-exact=true`  

이후, 프로젝트를 생성할 폴더로 접근하여 리액트 네이티브 프로젝트를 생성하자.  
`react-native init rnTestApp`  

이제 iOS 시뮬레이터를 한 번 실행해보자.  
프로젝트를 만든 폴더로 접근하여 iOS 시뮬레이터를 실행시켜보자.  
```
cd rnTestApp
react-native run-ios
```

안드로이드는 에뮬레이터를 실행하는 것보다 디바이스를 연결하여 아래 명령어를 실행하는게 더 속편하다.  
```
react-native run-android
```

