# [Unreal Engine] KRPG
## 1. 소개

<div align="center">
  <img src="https://github.com/k660323/KRPG/blob/main/Images/Main.png" width="99%" height="720"/>
  
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
   
#### **로그인 씬**
+ LoginScene
  + 해당 씬만의 기능 수행 및 특정 오브젝트 관리
    
+ UI_LoingScene
  + 각각 구현한 기능 관리 및 해당 기능들 끼리 쉽게 참조할 수 있도록 하는 클래스

##### **회원 가입**
+ UI_Register
  + 회원가입 버튼 클릭시 CreateAccount()함수를 통해 사용자가 입력한 e-mail, ID, PW 기반으로 BackEnd에 사용자를 등록한다.

**과정**
1. FindCutstomId를 호출하여 결과를 bool형 반환 합니다.
2. 사용가능한 이메일이면 CustomSignUp을 호출해 iD,PW를 설정합니다.
3. 계정 생성이 완료되면 국가등록, 이메일 등록, 성공 알림 함수를 호출합니다.
    
[UI_Register.cs](https://github.com/k660323/FunnyLand/blob/main/Scripts/UI/Scene/UI_Register.cs)


##### **로그인**
+ UI_Login
  + 로그인 버튼 클릭시 LoginBtnClick() 함수를 통해 BackEnd에 해당 정보 전송 후 결과 반환
  + 올바른 정보면 해당 플레이어의 Json 데이터를 가져와 초기화
    
[UI_Login.cs](https://github.com/k660323/FunnyLand/blob/main/Scripts/UI/Scene/UI_Login.cs)


##### **ID, PW 찾기**
+ UI_FindAccount
  + FindID - 계정 등록시 작성한 email로 ID를 메일로 발송
  + ResetPW - 계정 등록시 작성한 email, ID를 확인후 메일로 랜덤한 PW 발송
    
[UI_FindAccount.cs](https://github.com/k660323/FunnyLand/blob/main/Scripts/UI/Popup/UI_FindAccount.cs)

<br>

---

<br>

#### **로비 씬**
+ LobbyScene
  + 해당 씬만의 기능 수행 및 특정 오브젝트 관리
  + 포톤 네트워크 로비에 입장 초기화 기능 수행
    
[LobbyScene.cs](https://github.com/k660323/FunnyLand/blob/main/Scripts/Scenes/LobbyScene.cs)
            
+ UI_LobbyScene
  + OnRoomListUpdate함수가 일정 주기 마다 콜백함수로 생성된 방 리스트 불러온다.
  + 해당 씬에선 방생성, 방입장, 내정보, 상점, 옵션 설정이 가능합니다.
    
[UI_LobbyScene.cs](https://github.com/k660323/FunnyLand/blob/main/Scripts/UI/Scene/SceneUI/UI_LobbyScene.cs)
            
+ UI_FindRoom (방 찾기 및 입장)
  + OnRoomListUpdate 함수에 들어온 방 정보들을 UI에 띄어주는 클래스
  + 콜백으로 호출된 OnRoomListUpdate가 해당 클래스가 활성화 되어 있다면 SetRoomInfo() 호출
  + 입장하려고하는 방의 인덱스로 리스트 배열의 방 정보를 가져와 해당 정보가 존재하고 만약 패스워드가 존재시 패스 워드 까지 입력받습니다.
  + 방 최대 인원에 초과하는지 확인하고 조건을 충족시 PhotonNetwork.JoinRoom()을 호출하여 방에 입장합니다.
    
[UI_FindRoom.cs](https://github.com/k660323/FunnyLand/blob/main/Scripts/UI/Popup/UI_FindRoom.cs)
            
+ UI_RoomPW (방 입장 비밀번호)
  + UI_FindRoom에서 시각화된 정보들중 만약 비밀번호를 설정 해놓으면 뜨는 팝업 UI
  + 설정된 암호를 기입해야 방에 입장할 수 있다.
    
[UI_RoomPW.cs](https://github.com/k660323/FunnyLand/blob/main/Scripts/UI/Popup/UI_RoomPW.cs)
              
+ UI_CreateRoom (방 생성)
  + 방 생성 버튼을 통해 해당 PopUp클래스인 UI_CreateRoom 생성
  + 방제목, 비밀번호, 인원수, 라운드, 팀전, 팀킬, 공개방 여부를 설정 하여 방을 생성할 수 있습니다.
  + 설정한 정보들은 CreateRoom를 호출할 시 매개변수로 넣어주고, 외부에 보일 방 정보도 아래와 같이 세팅해서 생성합니다.
  + Managers.Photon.InitRoomProperties 함수는 사용자 지정 함수이며 RoomOption 객체를 생성해 로비에 보일 값을 설정하여 RoomOption을 반환하여 CreateRoom매개변수에 들어갑니다.
    
  [PhotonNetworkManager.cs](https://github.com/k660323/FunnyLand/blob/main/Scripts/Managers/Core/PhotonNetworkManager.cs)

[UI_CreateRoom.cs](https://github.com/k660323/FunnyLand/blob/main/Scripts/UI/Popup/UI_CreateRoom.cs)

       
+ UI_Room (방)
  + 방 설정, 유저 슬롯 설정, 채팅, 게임 준비 시작할 수 있는 UI입니다.
  + RequestUIPos(Player requestPlayer)
    + 마스터 클라이언트에게 해당 플레이어 UI위치를 요청하는 함수
  + SetUIPos(bool isInit, string parent)
    + 요청을 처리한 마스터 클라이언트가 UI위치를 대상 클라이언트에게 알리는 함수 첫 초기화면 대상 클라이언트 소유의 UI_Player 생성, 아닐시 대상 그룹(레드팀, 블루팀)에 추가
  + EditRoomOption()
    + 방설정창 호출
  + Ready()
    + 해당 플레이어 준비, UI_Player의 bool형인 ready변수가 수정된다. 이 변수는 OnPhotonSerializeView(PhotonStream stream, PhotonMessageInfo info)를 통해 콜백으로 모든 클라이언트에게 동기화 된다.
  + GameStart()
    + 마스터 클라이언트가 Ready시 호출, 팀전일 경우 선행 조건으로 팀 인원수 체크, Ready여부 체크하여 모든 플레이어가 Ready시 GameSceneLoad()함수를 RPC하여 모두 에게 알려 씬을 로드한다.
    
**방플레이어 이동**
1. 마스터 클라이언트가 처리
2. 마우스 클릭시 oNpOINTERdOWN()호출 대상 ui를 클릭하면 ui가 다른 ui에 가리지 않도록 SetAsLastSibling()호출
3. 마우스 클릭 중 OnPointerDrag() 호출 해당 UI가 마우스 포인터를 따라 움직인다.
4. 마우스 클릭을 땠을 때 OnPointerUp()호출 PointerUppOS()를 통해 Raycast를 한 후 리스트 중 UI_TeamRange를 가진 컴포넌트랑 충돌 했을 시 해당 UI를 MoveTeam()함수를 통해 이동 시킨다. 

[UI_Room.cs](https://github.com/k660323/FunnyLand/blob/main/Scripts/UI/Scene/SceneUI/UI_Room.cs)


+ UI_Player
  + 방에 입장한 플레이어 UI 입니다.
  + 해당 방에서 마스터 클라이언트와 클라이언트와 통신할 수 있는 매개체 입니다.
  + 플레이어 정보, UI 이동, 강퇴가 가능합니다.
    
[UI_Player.cs](https://github.com/k660323/FunnyLand/blob/main/Scripts/UI/Scene/UI_Player.cs)

<br>

---

<br>

#### **로딩 씬**
+ LoadingScene
  + 모든 플레이어가 게임 씬을 로딩후 동시에 진입하기 위한 씬
  + Init() ->  Managers.Scene.AsyncLoadScene(Define.Scene.Game) 해당 씬 비동기 로드
  + StartCoroutine(CorLoadingProgress); 비동기 로드 정보를 관찰하여 UI_LoadingScene에 알려 UI 업데이트하기 위해 코루틴 실행
  + 씬 로딩이 완료되면 PhotonNetwork.LocalPlayer.SetCustomProperties로 해당 상태 갱신
  + 만약 마스터 클라이언트면 CheckReadyPlayer() 코루틴을 실행해 모든 유저 씬 로드 체크
  + 모든 유저가 씬 로드가 완료되면 SceneActivation()를 RPC하여 모든 클라이언트에게 알려 게임씬에 진입한다.
    
[LoadingScene.cs](https://github.com/k660323/FunnyLand/blob/main/Scripts/Scenes/LoadingScene.cs)

<br>

---

<br>

#### **게임 씬**
+ GameScene
  + 게임씬에는 진행할 게임 컨텐츠를 지정하는 씬 입니다.
  + 여러 컨텐츠 씬에서 사용하는 기능들은 게임 씬에서 구현합니다.
  + 방장이 60초 동안 원하는 미니 게임을 선택해 플레이 하면 됩니다.
  + 최대 라운드는 게임 시작전 설정한 라운드를 따라가며 모든 라운드가 끝나면 개인전, 팀전에 따라 점수가 높은 유저 또는 팀이 승리합니다.
  + 컨텐츠 흐름은 FSM형식으로 구현된 StateController()함수를 통해 게임 상태를 제어 합니다.
    
[GameScene.cs](https://github.com/k660323/FunnyLand/blob/main/Scripts/Scenes/GameScene.cs)

**게임 흐름**
  1. UI_Chocie(맵선택) - [ChoiceMape.cs](https://github.com/k660323/FunnyLand/blob/main/Scripts/UI/Popup/UI_ChoiceMap.cs)
  2. UI_LoadMap(맵 로드) - [UI_LoadMap.cs](https://github.com/k660323/FunnyLand/blob/main/Scripts/UI/Popup/UI_LoadMap.cs)
  3. 해당 씬에 ContentsScene을 상속받은 클래스가 게임 시작 및 게임 종료 - [ContentsScene.cs](https://github.com/k660323/FunnyLand/blob/main/Scripts/Scenes/Contents/ContentsScene.cs)
  4. UI_RoundResult(점수 출력) - [UI_RoundResult.cs](https://github.com/k660323/FunnyLand/blob/main/Scripts/UI/Popup/UI_RoundResult.cs)
  5. 라운드 체크 - [ContentsScene.cs](https://github.com/k660323/FunnyLand/blob/main/Scripts/Scenes/Contents/ContentsScene.cs)
  6. 모든 라운드 수행시 게임종료 아닐시 1번부터 수행 - [UI_GameOver.cs](https://github.com/k660323/FunnyLand/blob/main/Scripts/UI/Popup/UI_GameOver.cs)

<br>

---

<br>

#### **컨텐츠 씬**
+ ContentsScene
  + 해당 컨텐츠 씬들은 위의 클래스를 상속받습니다.
  + 이 씬은 게임 시작, 종료 조건 설정, 종료 조건 보상, 게임 종료 등 다양한 게임 로직 흐름 제어를 수행합니다.
  + GameInit()는 게임 초기화및 시작을 담당하며 상속받은 클래스에서 이 함수를 override하여 각 컨텐츠에 맞게 흐름을 정의합니다.
  + GameEnd_M 함수는 게임이 종료 체크 및 종료를 수행합니다.
  + 해당 플레이어의 Properties를 수정하여 Photon 함수인 OnPlayerPropertiesUpdate가 호출되었을때 호출된다.
  + 수정된 Properties가 조건에 맞는 key를 포함하면 마스터 클라이언트가 endEvent 델리게이트가 구독한 함수들을 실행하면 된다.
  + OnPlayerPropertiesUpdate는 가상함수이며 게임 조건에 맞게 수정하면 된다.

### LastPeopleScene 게임 시작 흐름 예시 ###
1. Start()
2. GameInit()
3. RequestPos_ToM()를 마스터 클라이언트가 호출하도록 RPC
4. 마스터 클라이언트가 해당 RPC를 보낸 플레이어의 랜덤으로 자리 지정
5. CheckRequestCount를 호출해 모든 플레이어가 요청 했는지 체크
6. 만족시 봇과 플레이어 생성
7. 게임 시작

[ContentsScene.cs](https://github.com/k660323/FunnyLand/blob/main/Scripts/Scenes/Contents/ContentsScene.cs)

        
##### **LastPeopleScene**
  + AI사이에 들어간 플레이어들을 찾아 제거하면 되는 심플한 게임입니다.

[LastPeopleScene.cs](https://github.com/k660323/FunnyLand/blob/main/Scripts/Scenes/Contents/LastPeopleScene.cs)

**조작**
  + 플레이어와 AI 조작 로직은 FSM으로 구성되어 있습니다.

[LPPlayereController.cs](https://github.com/k660323/FunnyLand/blob/main/Scripts/Controllers/LastPeople/LPPlayerController.cs)


**공격**
1. FSM 상태가 Dead가 아니면 Attack상태로 전환이 가능합니다.
2. 피격 판정은 마스터 클라이언트에서 처리합니다.
3. BoxCastAll을 통해 피격된 모든 게임 오브젝트를 순회합니다.
4. 현재 공격 카운트가 최대 카운트랑 같으면 더 이상 반복문을 순회하지 않습니다.

[MeleeWeapon.cs](https://github.com/k660323/FunnyLand/blob/main/Scripts/Contents/Weapon/MeleeWeapon.cs)

5. 팀, 추가 효과 확인분 확인하는 OnAttack에서 Stat을 상속받은 클래스에서 소유자가 피격 처리를 하는 OnAttacked함수를 호출 합니다.

[Stat.cs](https://github.com/k660323/FunnyLand/blob/main/Scripts/Contents/Stat.cs)

   
**자기장**
  + 자기장은 총 5단계의 페이지가 존재하며 최종 페이지에 도달할 때 까지 계속해서 작아 집니다.
  + 게임 시작시 LastPeopleScene 클래스가 게임 시작인 PageStart함수를 호출합니다.
  + NextDestination()함수에서 다음 위치와 크기를 설정합니다.
  + 위치는 현재 자기장의 반지름 - 다음 자기장의 반지름의 차이를 구해 그 차이만큼 랜덤을 돌려 현재위치에 더하여 다음 위치를 구합니다.
  + 자기장 크기는 PageSize 배열에 있는 크기를 따라 갑니다.
  + PageCoroutine()을 통해 목적지와 크기에 대해 Perp하게 이동 됩니다.
  + 이동이 끝나면 타이머를 작동시키며 타이머가 끝나면 위의 루틴을 반복합니다.

[MagneticField.cs](https://github.com/k660323/FunnyLand/blob/main/Scripts/Contents/MagneticField.cs)
         
**레드존**
  + 게임 시작시 매 1분 마다 랜덤한 지역에 포격이 가해집니다.
  + 해당 포격을 맞으면 일격에 쓰러집니다.
  + 레드존 생성기와 레드존으로 이루어져 있습니다.

[RedZoneCreator.cs](https://github.com/k660323/FunnyLand/blob/main/Scripts/Contents/RedZoneCreator.cs)

[RedZone.cs](https://github.com/k660323/FunnyLand/blob/main/Scripts/Contents/RedZone.cs)


##### **LedgeBlocker**
  + 상단의 게이지가 다 닳을 때 가지 해당 캐릭터 색상이 맞는 버튼을 눌러 점수를 많이 획득하는 미니 게임
  + 모든 플레이어가 탈락하면 게임 종료
    
##### **ShootingShooter**
  + 제한 시간안에 최대한 많은 플레이어를 섬멸
  + 이동, 점프 공격 단순한 조작
  + 사망시 10초 뒤 리스폰

**조작**
  + FSM으로 플레이어 이동 로직 구현

[SSPlayerController.cs](https://github.com/k660323/FunnyLand/blob/main/Scripts/Controllers/ShootingShooter/SSPlayerController.cs)

**네트워크 오브젝트 ObjectPooling**
  + 모든 객체에 대한 처리가 어려워 자기 자신의 소유의 오브젝트들만 오브젝트 풀링을 부분적 적용
  + 조건을 만족하여 RegisterInsertQueue() 호출시 자신 객체면 오브젝트 풀링 아니면 비활성화
    
[Projectile.cs](https://github.com/k660323/FunnyLand/blob/main/Scripts/Contents/Projectile/Projectile.cs)

**ZombieSurviver**
  + 좀비를 피해 최대한 생존하는 미니게임
  + 캐릭터의 좌클릭으로 좀비나 플레이어를 밀어낼 수 있습니다.
  + 최후의 플레이어만 생존하거나 제한 시간안에 버티면 점수를 획득합니다.
    
**조작**
  + 플레이어와 AI조작 로직은 FSM으로 구현
    
**무기 효과**
  + 플레이어의 무기는 공격 시 해당 객체를 뒤로 날려버리는 특수 효과가 있습니다.
  + 플레이어는 CharacterController, AI는 NavMesh Agent를 사용하기에 유니티에서 제공하는 Rigidbody 컴포넌트를 사용할 수 없어 이를 둘다 사용할 수 있게 커스텀

+ Weapon
  + PhysicsEffect는 ScriptableObject로 정의되어 있고 특수 효과에 대한 정의가 되어있는 클래스 입니다. ex) 밀치기

[PhysicsEffect.cs](https://github.com/k660323/FunnyLand/blob/main/Scripts/Contents/Weapon/AdditionEffect/PhysicsEffect.cs)

  + Weapon의 OnAttack()에서 판정시 OnAddtionPhysicse를 호출하여 해당 효과가 있으면 적용
    
[Weapon.cs](https://github.com/k660323/FunnyLand/blob/main/Scripts/Contents/Weapon/Weapon.cs)

  + Controller3D에서 선언되어 있는 SetPhysics에서 매개변수로 온 값을 가지고 효과를 적용시킵니다.

[Controller3D.cs](https://github.com/k660323/FunnyLand/blob/main/Scripts/Controllers/BaseController/3D/Controller3D.cs) 

<br>

---

<br>

#### **기타**
+ UI_Chat
  + 룸 오브젝트
  + InputField에 보낼 텍스트를 입력 후 전송시, 포멧으로 플레이어 닉네임 삽입 후 포톤 서버에 전송하여 서버에서 모든 클라이언트에게 데이터 전송한다.
    
[UI_Chat.cs](https://github.com/k660323/FunnyLand/blob/main/Scripts/UI/Scene/UI_Chat.cs)
     
+ EnviromentController
  + 3D 게임의 경험을 다양하게 하기 위한 일종의 환경광 프리셋 클래스

## 환경광 동기화 ##
  + 마스터 클라이언트가 Start함수를 실행시 enviroments 배열 중에서 랜덤으로 선택
  + ApplyWeather함수를 RPC해서 모든 클라이언트의 환경과을 동일하게 맞춰줍니다.
    
[EnviromentController.cs](https://github.com/k660323/FunnyLand/blob/main/Scripts/Contents/EnviromentController.cs)

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
