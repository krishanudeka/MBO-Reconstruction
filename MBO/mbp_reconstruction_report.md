# 📄 Order Book Reconstruction from MBO Data - Technical Report

## ✅ Objective
This program processes a **Market By Order (MBO)** .csv file and reconstructs a **Market By Price (MBP-10)** order book snapshot. It outputs these snapshots to mbp_output.csv, showing the top 10 levels of bid and ask prices for a specific instrument.

## 🛠️ Key Features and Requirements

### ✔️ Inputs
- A **CSV file** (mbo.csv) containing MBO events (Add, Modify, Cancel).
- Required fields: ts_recv, ts_event, rtype, action, side, price, size, order_id, etc.

### ✔️ Outputs
- A **CSV file** (mbp_output.csv) with:
  - Bid/ask prices and sizes up to 10 levels.
  - Contextual metadata like timestamp, action, order ID, etc.

## ⚙️ Core Components & Logic

### 1. CSV Reader (csv_no_thread.h)
- Lightweight single-threaded CSV parser to extract rows field-by-field.

### 2. Order Management (Order struct)
- Maps order_id to its price, size, and side.
- Tracks active orders for fast removal or modification.

### 3. Books (bid_book, ask_book)
- bid_book: Sorted descending (std::greater) to show highest bid first.
- ask_book: Sorted ascending to show lowest ask first.
- Maintains size at each price level.

### 4. Action Handling (update_order_book)
- 'A' (Add): Adds new order to book and map.
- 'C' (Cancel): Removes order from both book and map.
- 'M' (Modify): Replaces old order with new details.
- Price/size validation via is_numeric() ensures data integrity.

### 5. Snapshot Writer (dump_mbp)
- Writes MBP-10 snapshot after every MBO event.
- Fixed format: 10 bid/ask levels each with price, size, count.
- Uses std::setprecision(2) for consistent float formatting.

## 🎯 Enhancements Over Previous Versions

| Feature | Improvement |
|--------|-------------|
| ✅ Accurate rtype override | Sets rtype = 10 to match expected MBP format |
| ✅ Fixed MBP-10 formatting | Outputs 10 bid + 10 ask levels in correct structure |
| ✅ Skips bad rows safely | Prevents crashes due to missing fields or bad data |
| ✅ Efficient maps | unordered_map and map provide O(1) order lookup and sorted MBP snapshot |
| ✅ Precision control | Ensures prices like 5.510000000 are formatted as 5.51 |

## 📊 Sample Output Columns
- index: Event number
- ts_recv, ts_event: Timestamps
- rtype, action, side, order_id: Event metadata
- bid_px_00, bid_sz_00, bid_ct_00, ... : Top 10 bids
- ask_px_00, ask_sz_00, ask_ct_00, ... : Top 10 asks

## ✅ Why This Code is Robust

- 💡 **Stable:** Skips invalid rows safely without crashing.
- 🚀 **Fast:** Uses unordered_map and map for efficient updates.
- 📏 **Standardized:** Matches the format of official mbp.csv reference files.
- 🔍 **Precise:** Includes both prices and sizes with formatting consistency.
- 🔁 **Reusable:** Easily extensible to support T/F actions or other message types.

## 🧩 Assumptions Made

- Order IDs are **unique** and persist across events.
- Action 'M' is equivalent to 'C' followed by 'A'.
- depth is unused in MBO but included as "0" in MBP output.
- Only numeric values are accepted for price, size, and order_id.

## 📌 File Structure

| File | Description |
|------|-------------|
| main.cpp | Main order book processing and MBP writer |
| csv_no_thread.h | Custom lightweight CSV parser |
| mbo.csv | Input MBO events |
| mbp_output.csv | Output MBP-10 snapshots |

## 🏁 Conclusion

This program is a clean, efficient, and correct implementation of **MBP-10 order book reconstruction from MBO feed**. It is tailored to handle real-time events while producing consistent and structured output suitable for further analysis or benchmarking. 
and this is the report for the project 
