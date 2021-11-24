## data-structure
> 때로는 클래식한 공부가 최고지 🤭  
> 자료구조 이론 공부하며 기초 탄탄히하기 ✨  

### 끄적끄적
- Stack이 활용되는 경우
    - 문서 Editor에서 되돌리기 기능을 구현할 때
    - Function Call에서 Return Address를 기억해야 할 때
- Queue가 활용되는 경우
    - 동영상 스트리밍에서 Buffering 데이터를 모아둘 때
    - 프린트 등 기기에서 작업 리스트를 구현할 때
- Deque이란?
    - Queue의 front와 rear에서 모두 삽입과 삭제가 가능
        - add_front, delete_front = Stack의 push, pop
        - add_rear, delete_front = Queue의 enqueue, dequeue
- Pointer의 종류
    - void *p: 임의 자료형의 주소를 저장하기 위한 포인터
    - int *pi: int 변수의 주소를 저장하기 위한 포인터
    - float *pf: float 변수의 주소를 저장하기 위한 포인터
    - char *pc: char 변수의 주소를 저장하기 위한 포인터
    - int **pp: 포인터 변수의 주소를 저장하기 위한 포인터
    - Test *ps: Test 구조체의 주소를 저장하기 위한 포인터
    - void (*f)(int): int를 매개변수로 갖고, 반환이 없는 함수의 주소를 저장하기 위한 포인터
- 정적 메모리 할당의 특징
    - 메모리의 크기가 프로그램이 컴파일 될 때 결정됨
    - 생성과 제거가 자동으로 이뤄져 프로그램 개발자의 개입 X
    - 해당 프로그램 블록이 끝나면 자동으로 할당 해제됨
- 동적 메모리 할당의 특징
    - 프로그램 실행 중에 메모리 크기를 결정함
    - 필요한 만큼만 할당하고 해제하므로 메모리의 효율적 사용
    - 프로그램 개발자가 메모리 생성과 해제를 직접 관리
- malloc(int size)
    - size 크기만큼 메모리를 할당
    - 메모리 블록의 시작 주소를 반환함
    ```c
    char *pc = (char*)malloc(5);
    int *pi = (int*)malloc(sizeof(int));
    ```
- calloc(int num, int size)
    - 배열 형식의 메모리를 할당함
    - size 만큼 배열 요소의 크기 설정
    - 할당되는 개수는 num으로 설정
- free(void *ptr)
    - 동적으로 할당된 메모리 블록을 시스템에 반납함
    - ptr은 할당되었던 메모리 블록을 가리키는 주소값
    ```c
    free(pi);
    ```
- Linked List의 특징
    - 노드들은 메모리의 어느 곳에나 위치할 수 있다
    - 노드들의 순서가 연결 리스트상의 순서와 동일하지 않다
    - 연속적인 기억공간이 없어도 데이터를 저장하는 것이 가능하다
- 재귀호출의 시스템 스택 변화과정
> ![factorial_stack_change_flow](https://user-images.githubusercontent.com/20378368/141251945-2c637b82-c2e0-4f79-9b36-99dd91b79873.png)
- Tree 용어 정의
    - degree: 트리가 가지고 있는 노드의 차수 중에서 가장 큰 값
    - level: 트리의 각 층에 번호를 매기는 것
    - Parent(부모) - Sibling(형제) - Child(자식)
    - leaf: 자식 노드가 없는 단말 노드
- Binary Tree
    - full binary tree: 트리의 각 레벨에 노드가 꽉 차있는 이진트리
    - complete binary tree: 1부터 k-1까지 노드가 꽉 차있고, 마지막 k에서는 오른쪽으로 노드가 순서대로 채워진 이진트리
- Traversal
    - Preorder: 전위 순회, VLR
    - Inorder: 중위 순회, LVR
    - Postorder: 후위 순회, LRV
- AVL Tree
    - Balance Factor: 왼쪽 서브 트리의 높이 - 오른쪽 서브 트리의 높이
    - Balance Factor의 차이가 1 이하인 이진탐색트리
    - 이진탐색트리에서 항상 균형 트리를 보장 = O(logn)
- AVL Tree Rotation
    - LL 회전: A부터 N까지 경로상의 노드들을 오른쪽으로 회전
    - LR 회전: A부터 N까지 경로상의 노드들을 왼쪽(RR)-오른쪽(LL)으로 회전
    - RR 회전: A부터 N까지 경로상의 노드들을 왼쪽으로 회전
    - RL 회전: A부터 N까지 경로상의 노드들을 오른쪽(LL)-왼쪽(RR)으로 회전
> ![maxresdefault](https://user-images.githubusercontent.com/20378368/143194964-68140182-2209-4d8a-8531-5b7ef3955593.jpg)