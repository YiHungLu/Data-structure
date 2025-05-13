透過深度優先搜尋（DFS）的方式，自動從迷宮的起點（左上角）走到終點（G），支援兩種任務模式：

任務一：找單一個出口（G）

任務二：找出通過多個出口（多個 G）的路徑，數量由使用者指定

input 範例:
6 6     <欄數> <列數>
EEEEOO  E：起點（實際程式從 (0,0) 起始）
OEOEEE  O：障礙，不能通行
GEEEOE  G：目標終點（出口）
OOEOOE
EEEOOO
OOEEEE

output 範例:
VVVVOO  輸出走過的路徑（V）
OEOVVV
GVVVOV
OOVOOV
VVVOOO
OOVVVV

RRRROO  與正確的路徑（R）
OEOREE
GRRROE
OOEOOE
EEEOOO
OOEEEE

程式執行:
0：離開
1：找一個出口
2：找多個出口（需輸入要找幾個 G）
