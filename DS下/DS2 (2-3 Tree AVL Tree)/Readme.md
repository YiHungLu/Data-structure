# Search Tree Utilities

此專案實作了兩種資料結構：**2-3 Tree** 與 **AVL Tree**，並提供介面讓使用者可以：
1. 建立 2-3 Tree 並顯示內容。
2. 建立 AVL Tree 並顯示內容。
3. 在 AVL Tree 上執行 Top-K 搜尋。

## 執行
*** Search Tree Utilities **
* 0. QUIT                  *
* 1. Build 2-3 tree        *
* 2. Build AVL tree        *
* 3. Top-K search on AVL tree *
*************************************
Input a choice(0, 1, 2, 3):

## 功能說明

### 1. Build 2-3 Tree (選項 1)
- 從指定的 `inputX.txt` 檔案中讀取大學資料（需使用者輸入檔案編號 `X`）。
- 根據學校名稱建構 2-3 Tree。
- 顯示：
  - Tree 高度。
  - 節點數。
  - 每筆資料的編號與資訊（如：學校名稱、科系、學制、畢業人數等）。

### 2. Build AVL Tree (選項 2)
- 以 2-3 Tree 中的資料為基礎，根據「畢業人數」為 key 建構 AVL Tree。
- 顯示：
  - Tree 高度。
  - 節點數。
  - 每筆節點中資料的編號與資訊。

### 3. Top-K Search on AVL Tree (選項 3)
- 讓使用者輸入 `K`，搜尋畢業人數最多的前 K 筆資料並顯示。

