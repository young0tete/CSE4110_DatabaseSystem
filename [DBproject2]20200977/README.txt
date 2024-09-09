Writer: 20200977 한영태

Usage:
***Line 15 to 17: 로컬 서버에 맞는 host, user, pw를 설정해야 합니다.***

1. TYPE Selection Menu
	0~7 사이의 integer를 입력해야 함.
	1~7을 입력 -> 각 TYPE을 실행시킴
	0을 입력	-> 프로그램이 정상적으로 종료됨

2. SUBTYPE Selection Menu for TYPE 1
	0을 입력 -> TYPE Selection Menu로 돌아감
	1을 입력 -> TYPE 1-1 실행

3. SUBTYPE Selection Menu for TYPE 2
	0을 입력 -> TYPE Selection Menu로 돌아감
	1을 입력 -> TYPE 2-1 실행

4. SUBTYPE Selection Menu for TYPE 3
	0을 입력 -> TYPE Selection Menu로 돌아감
	1을 입력 -> TYPE 3-1 실행
	2을 입력 -> TYPE 3-2 실행

5. TYPE 3-1
	해당 TYPE은 연산을 위한 k값을 입력하도록 되어있음.
	k는 정수를 입력해야 하며, 조건을 만족하는 agent의 수보다 k가 큰 경우 agent의 수만큼의 튜플을 출력함

6. SUBTYPE Selection Menu for TYPE 4
	0을 입력 -> TYPE Selection Menu로 돌아감
	1을 입력 -> TYPE 4-1 실행
	2을 입력 -> TYPE 4-2 실행

7. TYPE 6
	해당 TYPE은 buyer와 date를 입력하게 되어있음
	buyer: 1~5사이의 정수를 입력. (사전에 지정해둔 buyer 후보 5명이 prompt에 뜬다)
	date: YYYY-MM-DD 형식에 맞게 입력해야 함. 실존하지 않는 날짜 (ex.2023-13-00)를 입력하거나 형식에 맞지 않는 입력을 하는 경우에는 에러와 함께 프로그램이 종료됨
	사전에 준비해둔 property는 5개로 TYPE 6를 5번 실행해 5번 입력하는 경우 더이상 매물이 없다는 메시지가 출력됨

8. TYPE 7
	해당 TYPE은 agent ID, first name, last name을 입력하도록 되어있음
	agent ID: 0000-00000 형식에 맞게 입력해야함 (ex. 2301-30219)
	first name: 입력하는 string의 최대 길이는 100자임
	last name: 입력하는 string의 최대 길이는 100자임
