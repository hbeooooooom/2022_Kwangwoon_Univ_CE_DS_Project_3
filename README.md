## DS_Project3_2022_2
### 2022-2 Data Structure Project #3



##### 본 프로젝트에서는 그래프를 이용해 그래프 연산 프로그램을 구현한다. 이 프로그램은 그래프 정 
보가  저장된  텍스트  파일을  통해  그래프를  구현하고, 그래프의  특성에  따라  BFS,  DFS,  Kruskal, 
Dijkstra,  Bellman-Ford  그리고  FLOYD  연산을  수행한다. 그래프  데이터는  방향성(Direction)과 
가중치(Weight)를 모두 가지고 있으며, 데이터 형태에 따라 List 그래프와 Matrix 그래프로 저장한 
다. BFS와 DFS는 그래프의 방향성과 가중치를 고려하지 않고, 그래프 순회 또는 탐색 방법을 수행 
한다. Kruskal 알고리즘은 최소 비용 신장 트리(MST)를 만드는 방법으로 방향성이 없고, 가중치가 
있는 그래프 환경에서 수행한다. Dijkstra 알고리즘은 정점 하나를 출발점으로 두고 다른 모든 정점 
을 도착점으로 하는 최단경로 알고리즘으로 방향성과 가중치 모두 존재하는 그래프 환경에서 연산을 
수행한다. 만약 weight가 음수일 경우 Dijkstra는 에러를 출력하며, Bellman-Ford에서는 음수 사 
이클이  발생한  경우  에러, 음수  사이클이  발생하지  않았을  경우  최단  경로와  거리를  구한다. 
FLOYD에서는 음수 사이클이 발생한 경우 에러, 음수 사이클이 발생하지 않았을 경우 최단 경로 행 
렬을  구한다. 프로그램의  동작은  명령어  파일에서  요청하는  명령에  따라  각각의  기능을  수행하고, 
그 결과를 출력 파일(log.txt)에 저장한다.
각 그래프  연산들은  ‘GraphMethod’  헤더  파일에  일반  함수로  존재하며, 그래프  형식(List, 
Matrix)에 상관없이  그래프  데이터를  입력받으면  동일한  동작을  수행하도록  일반화하여  구현한다. 
또한 충분히 큰 그래프에서도 모든 연산을 정상적으로 수행할 수 있도록 구현한다.

![1](https://github.com/hbeooooooom/2022_Kwangwoon_Univ_CE_DS_Project_3/blob/main/readmdpng/1.png)


☐ Program implementation 
1. 그래프 데이터
프로그램은  그래프  정보가  저장되어  있는  텍스트  파일(graph_M.txt  또는  graph_L.txt)을 읽어, 
해당 정보를 Adjacency List 또는 Adjacency Matrix에 저장한다. 텍스트 파일의 첫 번째 줄에는 
그래프의 형식 정보(L: List, M: Matrix)가 저장되어 있고 두 번째 줄에는 그래프 크기가 저장되어 
있다. 이후 데이터는 그래프 형식에 따라 구분된다. List그래프의 경우 표1-1과 같이 edge의 출발 
vertex를 의미하는 데이터(형식-1),  edge의 도착 vertex와 weight가 쌍으로 이루어진  데이터(형식 
-2)로 구성된다. 만약 edge가 없는 vertex의 경우 (형식-1)만 존재할 수 있다. Matrix그래프의 경 
우 표1-2의 (형식-3)과 같이 그래프의 정보가 저장되어 있다. 행렬의 행과 열은 각각 to vertex와 
from vertex를 의미하고, 행렬의 값은 from vertex와 to vertex 사이를 잇는 edge의 weight를 의 
미한다. 이때, 그래프의 모든 vertex의 값은 0 이상의 정수이며, 0부터 시작하여 1, 2, 3, 4... 순으 
로 정해진다고 가정한다.
텍스트 파일에 포함되어 있는 그래프의 형식 및 그래프 크기 정보는 ‘Graph’ 클래스에 저장하며, 
그래프 연결 정보는 그래프 형식에 따라 알맞은 ‘그래프 클래스’에 저장한다. Adjacency List 정보 
는 ‘ListGraph’  클래스에  저장하고  Adjacency  Matrix  정보는  ‘MatrixGraph’  클래스에  저장한다. 
그래프 클래스들은 ‘Graph’ 클래스를 상속받는다. 그래프 정보가 포함되어 있는 텍스트 파일의 형 
식은 그림 2-1과 그림 2-2와 같다. 각 클래스의 멤버 변수에 대한 자세한 내용은 ‘구현 시 반드시 
정의해야하는 Class 및 멤버 변수’에 작성되어 있다

![2](https://github.com/hbeooooooom/2022_Kwangwoon_Univ_CE_DS_Project_3/blob/main/readmdpng/2.png)


2. 그래프 연산
프로그램은 텍스트 파일로부터 그래프 정보를 읽은 뒤, 명령어에 따라 그래프 특성에 맞는 그래프 
연산을 수행할 수 있다.
- BFS, DFS, DFS_R
각 명령어는  방향성과  가중치가  없는  그래프에서  수행  가능하므로  방향성과  그래프의  가중치가 
없다고 가정하고 수행한다. 프로그램은 각 명령어와 함께 입력받은 vertex를 시작으로 각 명령어에 
맞는 알고리즘을 이용하여 모든 vertex들을 방문하고, vertex의 방문 순서를 명령어의 결과로 출력 
한다. 이때, 각 명령어는  vertex의 값이  작은  vertex를 먼저  방문한다고  가정한다. BFS  명령어는 
Queue를, DFS  명령어는  Stack을 이용하여  동작하고  DFS_R  명령어의  경우  함수의  재귀적  호출 
방법을 사용하여 동작한다.
- KRUSKAL
Kruskal 명령어는 방향성이 없고 가중치가 있는 그래프에서 수행 가능하다. 프로그램은 Kruskal 
명령어  수행  시, 저장되어  있는  그래프  연결  정보를  이용하여  해당  그래프에  대한  MST를 구하는 
동작을 수행한다. 이때, MST를 구하는 과정에 있어서 sub-tree가 cycle을 이루는지에 대한 검사를 
수행하도록 한다.
- DIJKSTRA
Dijkstra 명령어는 방향성과 가중치가 있는 그래프에서 수행 가능하다. 프로그램은 명령어와 함께 
입력받은 vertex를 기준으로 Dijkstra 알고리즘을 수행한 후, 모든 vertex에 대해 shortest path를 
구하고, shortest path에 대한 cost 값을 구한다.
- BELLMANFORD
Bellmanford 명령어는  Start Vertex와 End Vertex를 입력으로 받아  최단 경로와  거리를 구한 
다. Weight가 음수인 경우에도 정상 동작하며, 음수 Weight에 사이클이 발생한 경우에는 알맞은 에 
러를 출력한다.
- Floyd
Floyd  명령어는  입력  인자  없이  모든  쌍에  대해서  최단  경로  행렬을  구한다.  Weight가  음수인 
경우에도 정상 동작하며, 음수 Weight에 사이클이 발생한 경우에는 알맞은 에러를 출력한다.
3. 정렬 연산
정렬  연산은  Kruskal  알고리즘의  edge를 정렬하는  데 사용한다. 연산의  효율을  향상하기  위해 
segment size에 따라 정렬 알고리즘을 구현한다. 해당 프로젝트에서는 퀵 정렬을 수행하며 정렬 수 
행 시 segment size를 재귀적으로 분할 할 때, segment size가 6 이하일 경우 삽입정렬을 수행하 
며, segment size가 7 이상인 경우엔 분할한다. 정렬은 제공된 의사코드에 기반하여 작성한다


![3](https://github.com/hbeooooooom/2022_Kwangwoon_Univ_CE_DS_Project_3/blob/main/readmdpng/3.png)
