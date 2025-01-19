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
  + 기술 데모에 쓰일 캐릭터들의 공통적으로 사용할 기능들을 정의해놓은 클래스 (무기, 상태머신 등)
  + 스탯, 상태 초기화 가상 함수 존재

[CharacterBase.h](https://github.com/k660323/KRPG/blob/main/Source/KRPG/Actor/CharacterBase.h) / [CharacterBase.cpp](https://github.com/k660323/KRPG/blob/main/Source/KRPG/Actor/CharacterBase.cpp)


#### **플레이어**
+ CharacterPlayer
  + CharacterBase를 상속받은 플레이어 전용 클래스
  + 플레이어가 사용할 기능을 정의한 클래스 (카메라, 인벤토리, 장비)
 
[CharacterPlayer.h](https://github.com/k660323/KRPG/blob/main/Source/KRPG/Actor/Player/CharacterPlayer.h) / [CharacterPlayer.cpp](https://github.com/k660323/KRPG/blob/main/Source/KRPG/Actor/Player/CharacterPlayer.cpp)


#### **몬스터**
+ CharaceterMonster
  + CharacterBase를 상속받은 몬스터 전용 클래스
  + 몬스터 이름과 체력을 나타내는 UWidgetComponent를 정의 및 초기화 또는 이벤트 바인딩
  + 스탯, 상태 등 초기화 가상 함수 구현

[CharacterMonster.h](https://github.com/k660323/KRPG/blob/main/Source/KRPG/Actor/Monster/CharacterMonster.h) / [CharacterMonster.cpp](https://github.com/k660323/KRPG/blob/main/Source/KRPG/Actor/Monster/CharacterMonster.cpp)

<br>

---

<br>

### **Controller**
+ PlayerControllerBase
  + 플레이어의 조작을 담당하는 클래스
  + EnhancedInput을 이용하여 구현
  + 이동, 점프, 카메라 이동, 줌 기능은 해당 클래스에서 함수로 만들어 바인딩
  + 공격, 구르기, 스킬, 인벤토리, 스탯, 장비창 아이템 줍기 기능들은 KRPGInputComponent클래스에서 InputConfig로 정의해놓은 입력 데이터 기반으로 바인딩하여 Tag에 따라 AbilityInputTagReleased에서 처리하도록 구현
 
[PlayerControllerBase.h](https://github.com/k660323/KRPG/blob/main/Source/KRPG/ControllerEx/Player/PlayerControllerBase.h) / [PlayerControllerBase.cpp](https://github.com/k660323/KRPG/blob/main/Source/KRPG/ControllerEx/Player/PlayerControllerBase.cpp)


+ MonsterAIControllerBase
  + 상태 머신에 사용될 데이터를 캐싱해놓은 클래스 (추적 시작 위치, 추적 대상 등)

[MonsterAIController.h](https://github.com/k660323/KRPG/blob/main/Source/KRPG/ControllerEx/Monster/MonsterAIControllerBase.h) / [MonsterAIController.cpp](https://github.com/k660323/KRPG/blob/main/Source/KRPG/ControllerEx/Monster/MonsterAIControllerBase.cpp)


<br>

---

<br>

### **FSM**
+ StateMahcine
  + 캐릭터들의 상태를 관리하는 클래스

[StateMahcineComponent.h](https://github.com/k660323/KRPG/blob/main/Source/KRPG/StateMachine/StateMachineComponent.h) / [StateMachineComponent.cpp](https://github.com/k660323/KRPG/blob/main/Source/KRPG/StateMachine/StateMachineComponent.cpp)


+ BaseState
  + 모든 상태에서 사용되는 기능들을 정의한 클래스
  + 이 클래스를 상속받아 추상 클래스를 구현하여 상태를 구현한다.

[BaseState.h](https://github.com/k660323/KRPG/blob/main/Source/KRPG/State/BaseState.h) / [BaseState.cpp](https://github.com/k660323/KRPG/blob/main/Source/KRPG/State/BaseState.cpp)

--추상 클래스--

| 함수명 | 설명 |
|:---:|:---|
| OnCheckEnterState | ●  상태 진입 조건을 확인하는 함수 리턴값은 boolean |
| OnEnterState | ●  상태 진입시 초기화 함수 |
| OnTickState | ●  상태 진입 조건을 확인하는 함수 리턴값은 boolean |
| OnExitState | ●  상태 전환시 현재 상태를 초기화 하는 함수 |

<br>

---

<br>


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
