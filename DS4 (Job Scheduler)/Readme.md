# 工作排程與模擬程式

## 程式概述

此程式旨在處理一組工作資料，並執行兩個主要功能：排序工作項目及模擬工作處理過程。程式包含以下功能：

1. **排序（Sort）**：讀取原始工作資料並依照到達時間進行排序，使用兩種排序算法（Shell Sort 和 Insertion Sort）來排序工作，並將排序結果輸出到新檔案中。
   
2. **模擬（Simulation）**：根據已排序的工作資料，進行工作排程模擬，並生成包含每個工作的處理結果、平均延遲時間和成功率的報告。

## 使用方式

### 1. 運行程式

程式啟動後會顯示選單，您可以選擇以下操作：

0: 結束程式
1: 排序工作
2: 模擬工作排程

### 2. 排序功能

- 輸入 `1` 以排序工作資料。您將需要提供一個工作資料檔案（`inputX.txt`），其中 `X` 代表檔案的編號。程式會將排序結果輸出到 `sortedX.txt` 檔案中。

- 目前支援兩種排序算法：
  - Shell Sort
  - Insertion Sort

  程式將依序進行兩種排序，並顯示排序所需的時間。

### 3. 模擬功能

- 輸入 `2` 以開始模擬工作排程。您將需要提供一個已排序的工作資料檔案（`sortedX.txt`）。程式會執行模擬過程並將結果輸出到 `outputX.txt` 檔案中。結果會包含以下內容：
  - 取消的工作清單（包括工作識別碼、取消時間和延遲時間）
  - 完成的工作清單（包括工作識別碼、完成時間和延遲時間）
  - 平均延遲時間
  - 成功率（已完成工作數與總工作數的比例）