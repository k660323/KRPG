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
      
#### **코어 매니저**

+ DataManager - 데이터 관리 매니저
+ InputManager - 사용자 입력 관리 매니저
+ ParticalManager - 파티클 생성 유틸
+ PhotonNetworkManager - 포톤 네트워크 객체 관리 매니저
+ PoolManager - 오브젝트 풀링 매니저
+ ResourceManager - 리소스 매니저
+ SceneManager - 씬 매니저
+ SoundManager - 사운드 매니저
+ UIManager - UI 매니저

        
#### **컨텐츠 매니저**

+ GameManager
  + 네트워크에 존재하는 게임 오브젝트를 서치, 씬 정보, 소유 플레이어, 관전 등 각종 유틸 클래스
  + 네트워크 오브젝트들은 고유의 ViewId를 가지고 있어 이를 key로 이용해 자료구조 Dictionary<key, GameObject>형태로 저장
  + BaseController를 상속받는 모든 클래스가 AWake()를 실행 시 SetPhotonObject함수 실행하여 등록하도록 설계
  + Photon은 룸오브젝트는 ViewID 0 ~ 999, 플레이어 오브젝트는 ViewID 1000번 이후로 플레이어당 1000개의 오브젝트들을 각각 할당 할 수 있습니다.

+ GameOptionManager
  + 게임 해상도, 그래픽 품질, 사운드, 마우스 감도 값들을 관리하는 매니저
  + Json파일로 데이터를 저장 및 불러옵니다.
  + UI_Preferences클래스에서 UI로 환경 설정하면 값이 반영됩니다.
         
[Managers.cs](https://github.com/k660323/FunnyLand/blob/main/Scripts/Managers/Managers.cs)

<br>

---

<br>
     
### **씬**

전체적인 씬은 로그인, 로비, 게임 선택, 게임 씬으로 나눠서 구현
   

#### **게임 씬**
+ GameScene
  + 게임씬에는 진행할 게임 컨텐츠를 지정하는 씬 입니다.
  + 여러 컨텐츠 씬에서 사용하는 기능들은 게임 씬에서 구현합니다.
  + 방장이 60초 동안 원하는 미니 게임을 선택해 플레이 하면 됩니다.
  + 최대 라운드는 게임 시작전 설정한 라운드를 따라가며 모든 라운드가 끝나면 개인전, 팀전에 따라 점수가 높은 유저 또는 팀이 승리합니다.
  + 컨텐츠 흐름은 FSM형식으로 구현된 StateController()함수를 통해 게임 상태를 제어 합니다.
    
[GameScene.cs](https://github.com/k660323/FunnyLand/blob/main/Scripts/Scenes/GameScene.cs)

<br>

---

<br>

#### **기타**


<br>

---

<br>

## 5. 구현에 어려웠던 점과 해결과정
+ Widget의 생명주기 때문에 초기화가 진행되지 않은 문제로 인해 구현에 어려움을 겪었습니다.
  +  
    
 
## 6. 느낀점
+ Unreal Engine은 Unity와 달리 게임 구조가 이미 잡혀져 있다 보니 기능을 이해하지 못해 컨텐츠로 응용하기 어려웠기에 Unreal Engine을 Unity처럼 자유자제로 다루기 위해 추가적인 학습의 필요성을 느꼈습니다.


## 7. 플레이 영상
+ https://www.youtube.com/watch?v=cyf_IUQBiYw
