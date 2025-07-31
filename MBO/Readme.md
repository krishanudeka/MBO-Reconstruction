# MBP-10 Reconstructor from MBO Data

This project reconstructs MBP-10 (Market By Price) snapshots from MBO (Market By Order) data using C++. The reconstructed data is written to a CSV file (`mbp_output.csv`) for further use in trading systems, analytics, or simulations.

---

## 📁 Project Structure

MBO/
├── .vscode/   # VSCode config files
│ ├── c_cpp_properties.json
│ ├── launch.json
│ └── settings.json
│
├── build/Debug/   # Compiled object and executable files
│ ├── main.o
│ └── outDebug.exe
│
├── main.cpp     # Main program logic
├── csv_no_thread.h     # Header-only CSV parser (Fast C++ CSV Parser)
├── mbo.csv      # Input file (raw MBO data)
├── mbp_output.csv      # Output file (MBP-10 data)
├── Makefile    # Build configuration
├── main.exe    # Built executable
└── mbp.csv     # Desired output file format (MBP-10)

---
```yaml

## 🚀 How to Run

### 🔨 Build the Executable

If you're using **Visual Studio Code**, your `.vscode` setup already supports debugging and building.

To build manually via terminal:

#### On Windows (MSVC):

```bash
cl /EHsc /std:c++17 main.cpp /Fe:main.exe

On Linux/macOS (G++):

```bash
g++ -std=c++17 main.cpp -o main

Or simply use:

```bash
make

---

📦 Input Format (mbo.csv)
Your input CSV (mbo.csv) should contain raw MBO data with the following columns:

```arduino 
ts_in_delta, ts_recv, ts_event, rtype, publisher_id, instrument_id, action,
side, depth, price, size, flags, ...

---

📤 Output Format (mbp_output.csv)
The output mbp_output.csv contains MBP-10 snapshots with fields like:

Metadata: index, ts_recv, ts_event, rtype, publisher_id, etc.

MBP-10 Levels: bid_px_00, bid_sz_00, ..., ask_ct_09

Additional Fields: symbol, order_id, flags, sequence

These fields provide a 10-level view of the bid and ask sides of the order book after every update.

---

🧩 Dependencies
This project uses a header-only CSV parser:
csv_no_thread.h (a modified version of Fast C++ CSV Parser)

No external libraries need to be installed for C++.

---

Visualizing the output in Python:

As we can notice, The Official records are overlapping with the Generated records, which means this model is providing high accuracy. 

![MBO](graphs\bid_price.jpg)
![MBO](graphs\ask_price.jpg)
![MBO](graphs\bid_size.jpg)
![MBO](graphs\ask_size.jpg)

---

📋 Python Requirements (requirements.txt)

```txt
pandas>=1.5.0
matplotlib>=3.5.0
numpy>=1.21.0
seaborn>=0.11.0
jupyterlab>=3.0.0

Install via:

```bash
pip install -r requirements.txt

---

📊 Example Command

```bash
./main.exe mbo.csv mbp_output.csv

---


🧑‍💻 Author
Developed by Bedagya Bordoloi.

```yaml
For questions or feedback, feel free to open an issue or connect on GitHub.


---