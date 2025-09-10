# TextRPG_SPARTA

## 프로젝트 소개

### 프로젝트 이름
- TextRPG_Sparta

### 프로젝트 개요
- 텍스트 기반의 턴제 RPG 게임!<br>
- 적과의 Battle을 통하여 더욱 강해져<br>
  Boss Monster를 쓰려트려 보세요!<br>

### 프로젝트 목적
- C++ , Git 사용법 숙달<br>
- 다른 프로그래머들과의 협업<br>

### 프로젝트 제작 기간
- 2025.09.03(수) ~ 2025.09.10(수)<br>

## 개발 환경

### 개발 언어 및 도구
IDE : Visual Studio 2022 (v143)<br>
Compiler : MSVC 17.14.12<br>
C++ : ISO C++14 표준(/std:c++14)<br>

## 프로젝트 구조

// TODO - 프로젝트 완성시 재작성 예정

```less
TextRPG_SPARTA
+---CSVParser                     // CSV -> Json 파싱 프로젝트
|   +---Main.cpp
+---Resources                     // CSV->Json 파싱용 데이터
|   |   CSVParser.exe
|   +---input                     // 파싱할 CSV
|   |       Enemy.csv
|   |       Item.csv
|   |       Shop.csv
|   \---output                    // CPP에서 읽을 Json
|           Enemy.json
|           Item.json
|           Shop.json
\---TextRPG_Sparta                // 메인 프로젝트 (TextRPG)
    |   BattleManager             // 전투 관련 매니저
    |   JsonParser.h              // Json 파싱 Helper용 클래스
    |   DataManager               // Json에서 사용할 데이터를 Vector 로 파싱
    |   EffectDescriptor.h        // Effect 관련 정의 모음
    |   EffectManager             // Item 등에서 사용할 '효과' 관리 매니저
    |   HealEffect                // 세부 효과 : 체력 회복
    |   IncreaseAttackEffect      // 세부 효과 : 공격력 증가
    |   EffectRegister.h          // 세부 Effect들이 등록하기 위한 Helper
    |   Enemy                     // Enemy 클래스
    |   EnemyData.h               // Data로 가져온 Enemy 관련 데이터 모음
    |   GameManager               // 게임 매니저 (전체적인 플레이 관리)
    |   ItemData.h                // Data로 가져온 Item 관련 데이터 모음
    |   ItemInstance              // 실제 생성하는 Item 클래스
    |   ItemManager               // Item Data를 관리하고 Item을 생성하는 매니저
    |   Main.cpp                  // Main 함수 진입점
    |   ShopBase                  // 
    |   ShopData.h                // 
    |   ShopManager               // 상점 총괄 Manager
    |   
    +---Character
    |       CharacterBase.h	// player, enemy의 베이스 클래스
    |       Player                // Player Class - Inventory, Gold,Exp, Level 관련 
```

## 핵심 로직 / 클래스

- EffectManager(map<string,Factory>)<br>
  : 아이템과 관련된 '효과' 구현시<br>
    Enum - Switch 대신 사용해보려 한 클래스<br>
    - EffectRegister를 통해 효과 구현 클래스에서 매니저에게 '등록'하는 형식을 취함<br>
    - 새로운 효과 구현에 따른 Switch 구문 수정을 막기 위함<br>
    - Manager에서는 주어진 Effect String에 따른 '효과'를 '생성'하여 반환(Factory)<br>

- DataManager<br>
  : Json 파싱 및 다른 매니저들에게 데이터를 넘겨주는 클래스<br>

- ItemManager<br>
  : ItemData를 DataManager에게 넘겨받고<br>
    ItemData 전반을 관리하고 ItemInstance를 생성해주는 클래스<br>

- GameManager<br>
  : 전반적인 시스템 초기화와 게임 진행을 담당<br>
- BattleManager<br>	
  :전투가 이뤄지는 클래스. 싱글톤으로 구성되어 get instance로 불러와서 startbattle을 호출하면 된다<br>
   전투가 시작되면 적을 랜덤으로 생성하고 적과 플레이어의 사망상태를 계속 체크한다.<br>
   전투가 끝나면 이 상태로 게임을 끝낼지 이어할지 결정하는 클래스이다<br>
- ShopManager<br>
   : 플레이어와 상점의 상호작용을 통해 아이템 거래를 관리<br>
- EnemySpawnManager<br>
- CharacterBase<br>
  :플레이어와 적들이 가지는 공통 스테이터스 혹은 공통으로 호출하는 함수들을 저장하는 클래스<br>
   isdead(), takedamage()로 서로 상호작용을 위한 혹은 상태 확인을 위한 함수들이 있다.<br> 
- Player<br>
  :사용자가 직접 움직이는 개체이며 아이템 인스턴스를 벡터로 저장한다.<br>
   레벨업 기능과, 벡터배열에서 하나를 찾아서 아이템을 샂게한다거나 하는 여러 기능이 있다.<br>
- Enemy<br>

// TODO - 작업자 분들의 관련 클래스 내용 추가 희망!

## 추가 구현 사항

### CSV-Json-CPP 파싱
세부 데이터를 수정할때마다 cpp 파일이 변경되거나<br>
빌드를 다시 하는 것이 귀찮기도 하고 그걸로 세부 git 로그가 남는 것이 마음에 들지 않는다<br>
-> 그냥 데이터만 바꿀수는 없나?<br>

라는 생각으로 시작한 데이터 파싱 관련 기능<br>

별도의 CSVParser라는 프로젝트를 '구글링' 과 'gpt'를 이용하여 구현하였고<br>
이후 Cpp에서 DataManager에서 각 Data 클래스들에 맞게 파싱을 하여 사용!<br>

### Item - Effect 구현
아이템 효과 구현 시 Enum-Switch 구문이 나름대로 지긋지긋하여 다른 방식이 없나 알아본 구현 방식<br>
(map<string,Factory>)<br>

추가 효과 구현에 따라서<br>
해당 파일만 만들고 Register 용 매크로 함수를 통해 등록하는 방식을 취하였다<br>

HealEffect.h / cpp 작성 후<br>
REGISTER_EFFECT_TYPE(HealEffect) 매크로 함수로<br>
EffectManager 등록 끝!<br>

이후, Item 쪽에서는<br>
Effect를 받아 Apply 만 호출하여 효과 성공여부를 파악하는 방식<br>

## UML

### Class

[![Image](https://github.com/user-attachments/assets/b443889f-baf6-4762-b7f7-1987fb175db5)](https://github.com/user-attachments/assets/b443889f-baf6-4762-b7f7-1987fb175db5)<br>

[drawIo](https://app.diagrams.net/#G1p9FV7qsxyYK5KyON9Qgbw5q-oTzeOcDd#%7B%22pageId%22%3A%22c4acf3e9-155e-7222-9cf6-157b1a14988f%22%7D)<br>

---

### Input Data
[![Image](https://github.com/user-attachments/assets/43b7e2db-a74f-4cce-8127-4bfc277848ea)](https://github.com/user-attachments/assets/43b7e2db-a74f-4cce-8127-4bfc277848ea)<br>

[drawIo](https://app.diagrams.net/?libs=general;uml#G1iOIti2LcJnMoZcF6xcrK-28HOZ-3vafa#%7B%22pageId%22%3A%22C5RBs43oDa-KdzZeNtuy%22%7D)<br>


## ETC...

### 트러블 슈팅 관련

[CSV-Json-Cpp 파싱 관련 인코딩 문제](https://www.notion.so/teamsparta/CSV-Json-Cpp-2642dc3ef514800dbf98e26e6c09cfff)<br>

[EffectFactory 관련 빌드 에러](https://www.notion.so/teamsparta/0904-EffectFactory-C2664-2642dc3ef51480d4bd12eea1c45b1509)<br>

---

### CSVParser 이용법

1. csv에 데이터를 수정한다<br>

<img width="1555" height="201" alt="Image" src="https://github.com/user-attachments/assets/42d52cb1-d757-4771-a759-2b4e10f611dd" /><br>

2. Resource 폴더로 올라간다<br>

3. Resource 폴더경로에서 cmd를 입력!<br>
   (이러면 해당 폴더 경로에서 cmd가 열림)<br>

<img width="1987" height="591" alt="Image" src="https://github.com/user-attachments/assets/1a129a65-7276-4e04-9592-c34f8eac7f3b" /><br>

4. 열린 Cmd 에서 'CSVParser.exe input output'을 입력<br>

<img width="997" height="185" alt="Image" src="https://github.com/user-attachments/assets/5f219469-2d05-4a4f-8a43-7aee38c954a9" /><br>

5. 엔터키 입력하면 파싱 진행 및 결과 표시<br>

<img width="932" height="185" alt="Image" src="https://github.com/user-attachments/assets/7b92dc25-335d-48ff-93e5-f27d9f5b2266" /><br>

6. TextRPG 프로젝트에서 결과 확인!<br>

<img width="1440" height="443" alt="Image" src="https://github.com/user-attachments/assets/52a8831a-d71f-4934-921d-3514ee8da427" /><br>

- 해당 중단점 위치는 DataManager의 Initialize() 마지막 줄<br>

- name이 보이지 않는 이유는 '인코딩' 때문<br>
  (name을 '영어'로 지은 경우는 '조사식'에서도 잘 보인다)<br>
  (일반 콘솔 출력시에는 정상 출력됨)<br>

### 요약
- 원하는 데이터로 csv 수정<br>
- CSVParser input output 을 cmd에서 입력<br>
- 바뀐 json 파일로 DataManager가 파싱됨<br>
