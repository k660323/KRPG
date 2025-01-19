# [Unreal Engine] KRPG
## 1. 소개

<div align="center">
  <img src="https://github.com/k660323/KRPG/blob/main/Images/Main.png" width="99%" height="520"/>
  
  < 게임 플레이 사진 >
</div>

+ KRPG란?
  + 싱글 RPG 요소를 구현한 기술 데모 포트폴리오
 
+ 목표
  + 언리얼 엔진 구조 및 기능 탐색
  
+ 구현
  + 캐릭터 이동 공격 및 스킬 구현
  + 스탯 구현
  + 인벤토리 구현
  + 장비창 구현
  + 아이템 구현
  + 몬스터 AI 구현
          

<br>

## 2. 프로젝트 정보

+ 사용 엔진 : Unreal Engine
  
+ 엔진 버전 : 5.1

+ 사용 언어 : C++
  
+ 작업 인원 : 1명
  
+ 작업 영역 : 기능 구현
  
+ 장르      : 기술 데모 RPG
  
+ 소개      : 언리얼 엔진에 구조 및 기능에 대해 알아보고 컨텐츠 구현
  
+ 플랫폼    : PC
  
+ 개발기간  : 2023.09.01 ~ 2023.10.08
  
+ 형상관리  : X

<br>

## 3. 사용 기술
| 기술 | 설명 |
|:---:|:---|
| 디자인 패턴 | ● **싱글톤** 패턴 Managers클래스에 적용하여 여러 객체 관리 <br> ● **FSM** 패턴을 사용하여 플레이어 및 AI 기능 구현 <br> ● **옵저버** 패턴을 사용하여 플레이어 상태, 스킬 상태를 변경시에만 UI 업데이트|


<br>

## 4. 구현 기능

### **구조 설계**

대부분 유니티 프로젝트에서 사용되고 자주 사용하는 기능들을 구현하여 싱글톤 클래스인 Managers에서 접근할 수 있도록 구현
      
#### **매니저**

+ KRPGAssetManager
  +  아이템, 몬스터, 플레이어 관련 데이터를 미리 로드해 캐싱해 놓은 싱글톤 매니저

[KRPGAssetManager.h](https://github.com/k660323/KRPG/blob/main/Source/KRPG/KRPGAssetManager.h) / [KRPGAssetManager.cpp](https://github.com/k660323/KRPG/blob/main/Source/KRPG/KRPGAssetManager.cpp)

<br>

---

<br>
     
### **캐릭터**

+ CharacterBase
  + 

#### **플레이어**
+ CharacterPlayer
  +
  

#### **몬스터**
+ CharaceterMonster
  + 


### **Controller**
+ PlayerControllerBase
  +

+ MonsterAIControllerBase
  + 

### **FSM**
+ StateMahcine
  + 

+ BaseState
  + 

### **인벤토리**
+

### **장비**
+

### **아이템**
+

### **능력치**
+

### **애니메이션**
+

<br>

---

<br>

#### **기타**

+ Define
  + 각종 Enum들을 정의하는 클래스

[Define.h](https://github.com/k660323/KRPG/blob/main/Source/KRPG/Define/Define.h)


+ KRPGGameplayTags
  + 언리얼에 지원하는 계층형 Tag, Enum 처럼 쓸수있는 것이 특징
  + 사용자 입력 Tag 정의

 [KRPGGameplayTags.h](https://github.com/k660323/KRPG/blob/main/Source/KRPG/KRPGGameplayTags.h) / [KRPGGameplayTags.cpp](https://github.com/k660323/KRPG/blob/main/Source/KRPG/KRPGGameplayTags.cpp)


<br>

---

<br>

## 5. 구현에 어려웠던 점과 해결과정
+ Widget의 생명주기 때문에 초기화가 진행되지 않은 문제로 인해 구현에 어려움을 겪었습니다.
  +  
    
 
## 6. 느낀점
+ Unreal Engine은 Unity와 달리 게임 구조가 이미 잡혀져 있다 보니 기능을 이해하지 못해 컨텐츠로 응용하기 어려웠기에 Unreal Engine을 Unity처럼 자유자제로 다루기 위해 추가적인 학습의 필요성을 느꼈습니다.
+ 다음번엔 일일히 GameplayTags정의를 직접 작성하지 말고 매크로로 Tag를 정의해보자.
+ StateMahcine 의 State 할당을 Controller를 상속받은 클래스에서 할당하도록 구현하는게 좋을것 같다. 왜냐하면 입력과 State 할당을 해당 클래스에서 수행하면 Controller 클래스를 모듈화하여 다양한 행동을 구현할 수 있을 것 같다. (ex 탈것)


## 7. 플레이 영상
+ https://www.youtube.com/watch?v=cyf_IUQBiYw
