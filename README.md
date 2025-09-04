# TextRPG_SPARTA

## 코딩 규칙

- 함수명 : Pascal 표기법<br>

- 변수명 : camel 표기법<br>

## Git Branch 작업 팁!

- Main은 최종 결과물로 사용할 예정<br>

- Dev를 집처럼 여기자<br>

- 작업에 따라 Dev를 기준으로 Feature 브랜치를 생성하고<br>
  작업 완료 후, Merge를 통해 Dev에 적용!<br>
  (이후 해당 Feature_Branch를 삭제하면 깔끔!)<br>

- Merge 하기 전에 fetch를 눌러<br>
  받을 데이터 있는지 확인하기!<br>

## 도움이 필요하면 공유하기!

- 팀 작업이므로 같이 문제를 공유하고 풀어나감으로서<br>
  서로 더욱 성장할 수 있습니다!<br>

- 아무리 해도 모르겠다 싶으면 구글링과 튜터님의 힘을 빌려봅시다!<br>

## 트러블 슈팅 기록하기!

- 메모장을 키고<br>
  발생한 문제를 적어두면<br>
  나중에 발표할때 어떤 트러블이 있었는지와<br>
  어떤 해결책으로 해결하였는지를 공유할 수 있습니다!<br>

## CSVParser 이용법

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

ps) 혹시 별도의 데이터 추가를 원하시는 분은 '현재훈'을 찾아주세요...<br>