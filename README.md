# MBO_Construction
# 📄 MBP-10 Order Book Reconstruction from MBO Data

This project reconstructs a **Market By Price (MBP-10)** snapshot from raw **Market By Order (MBO)** data using C++.  
It generates a structured `mbp_output.csv` file that captures the top 10 levels of bid and ask prices for real-time trading analysis, simulation, or backtesting.

---

## ✅ Objective

Transform high-frequency **MBO event data** into consistent and reliable **MBP-10 snapshots**, preserving order-level detail while summarizing at the price level.

---

## 🧠 Key Features

| Feature | Description |
|--------|-------------|
| 📥 **Input:** `mbo.csv` | Raw MBO events with fields like `action`, `side`, `price`, `size`, `order_id` |
| 📤 **Output:** `mbp_output.csv` | 10-level bid/ask summary with contextual metadata |
| ⚡ High Performance | Efficient use of `unordered_map` and `map` for fast access and sorting |
| 🛡️ Robustness | Gracefully handles malformed rows and invalid values |
| 🎯 Precision | Float formatting standardized using `std::setprecision(2)` |
| 🔄 Reusability | Modular logic that can be extended to handle new event types |

---

## 📦 Input Format – `mbo.csv`

Each row represents an order-level event:

``csv
ts_in_delta, ts_recv, ts_event, rtype, publisher_id, instrument_id,
action, side, depth, price, size, order_id, flags, ...


## 📤 Output Format – `mbp_output.csv`

Each row represents a full MBP-10 snapshot. Fields include:

- `index`, `ts_recv`, `ts_event`, `rtype`, `action`, `side`, `order_id`
- `bid_px_00`, `bid_sz_00`, `bid_ct_00`, ..., `bid_px_09`, `bid_sz_09`, `bid_ct_09`
- `ask_px_00`, `ask_sz_00`, `ask_ct_00`, ..., `ask_px_09`, `ask_sz_09`, `ask_ct_09`

---

## ⚙️ Core Components

### 🧩 `csv_no_thread.h`

- Lightweight single-threaded CSV parser
- Efficiently processes large `.csv` files
- No external dependencies required

### 🧱 Order Struct

- Tracks individual orders using `order_id` as key
- Stores `price`, `size`, and `side` for rapid lookup, modification, and deletion

### 📚 Bid & Ask Books

- `bid_book`: Sorted descending using `std::greater` for highest bid
- `ask_book`: Sorted ascending for lowest ask
- Maintains cumulative size per price level

### 🔄 Event Handler

- `'A'`: Add order to book
- `'M'`: Modify existing order by canceling and re-adding
- `'C'`: Cancel order and remove from books
- Invalid/missing data is safely skipped

### 📝 MBP Writer

- After every event, a full MBP-10 snapshot is dumped to the output
- 10 bid + 10 ask levels, each with:
  - Price (`px`)
  - Size (`sz`)
  - Count (`ct`)

---

## 🎯 Enhancements Over Previous Versions

| Feature                  | Improvement                                 |
|--------------------------|---------------------------------------------|
| ✅ `rtype` Normalization | Outputs `rtype = 10` for MBP consistency    |
| ✅ Standard MBP Format   | 20 levels (10 bid + 10 ask), correct order  |
| ✅ Row Validation        | Skips malformed rows safely                 |
| ✅ O(1) Order Lookup     | Uses `unordered_map` for speed              |
| ✅ Float Precision       | Cleans values like `5.510000000` → `5.51`   |

---

## 📊 Output Sample Fields

| Field          | Description                |
|----------------|----------------------------|
| `index`        | Event number               |
| `ts_recv`      | Timestamp received         |
| `ts_event`     | Actual event timestamp     |
| `rtype`        | Record type (fixed to 10)  |
| `action`       | Action code (`A`, `C`, `M`)|
| `side`         | Bid or Ask                 |
| `order_id`     | Unique order identifier    |
| `bid_px_00`... | Top 10 bid prices          |
| `ask_px_00`... | Top 10 ask prices          |
| `bid_sz_00`... | Size at each bid level     |
| `ask_sz_00`... | Size at each ask level     |

---

## 📊 Python Visualization

Output accuracy can be verified using Python scripts.  
The following graphs compare **official** vs **reconstructed** MBP data, showing strong overlap:

- 📉 **Bid Price**
- 📈 **Ask Price**
- 📊 **Bid Size**
- 📊 **Ask Size**

---

## 🐍 Python Requirements

Create a `requirements.txt` file with:

``txt
pandas>=1.5.0  
matplotlib>=3.5.0  
numpy>=1.21.0  
seaborn>=0.11.0  
jupyterlab>=3.0.0


## 🧱 Project Structure

| File            | Description                               |
|-----------------|-------------------------------------------|
| `main.cpp`      | Core logic for reading MBO, writing MBP   |
| `csv_no_thread.h` | Header-only CSV parser                   |
| `mbo.csv`       | Input raw MBO data                        |
| `mbp_output.csv`| Output MBP-10 snapshot                    |
| `mbp.csv`       | Sample reference output                   |
| `Makefile`      | Build instructions (Linux/macOS)          |

---

## 🔧 How to Build & Run

### 🛠️ Build

**Windows (MSVC):**
``bash
cl /EHsc /std:c++17 main.cpp /Fe:main.exe
