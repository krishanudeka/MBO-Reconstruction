📊 Order Book Reconstruction: MBO to MBP-10
Welcome to the Order Book Reconstruction project! This tool processes Market By Order (MBO) data from a CSV file and generates Market By Price (MBP-10) snapshots, capturing the top 10 bid and ask price levels for a financial instrument. The output is saved to mbp_output.csv, ready for analysis or integration into trading systems. Whether you're a developer, financial analyst, or curious learner, this project offers a robust and efficient way to explore order book dynamics.
🎯 Project Purpose
This program transforms raw MBO events (Add, Modify, Cancel) into structured MBP-10 snapshots, providing a clear view of the top 10 bid and ask prices at any given time. It’s ideal for:

Analyzing market depth and liquidity.
Studying order book behavior in financial markets.
Building or testing trading algorithms.

📋 Requirements
To run this project, ensure you have the following Python libraries installed:



Library
Version
Purpose



pandas
>=1.5.0
Data manipulation and analysis


matplotlib
>=3.5.0
Data visualization


numpy
>=1.21.0
Numerical computations


seaborn
>=0.11.0
Enhanced data visualization


jupyterlab
>=3.0.0
Interactive development


Install them using pip:
pip install pandas>=1.5.0 matplotlib>=3.5.0 numpy>=1.21.0 seaborn>=0.11.0 jupyterlab>=3.0.0

You’ll also need a C++ compiler (e.g., g++) to compile the main program.
🛠️ Key Features

Efficient Input Processing: Reads MBO events from mbo.csv with a lightweight, single-threaded CSV parser (csv_no_thread.h).
Dynamic Order Management: Tracks orders using an Order struct, mapping order_id to price, size, and side for quick updates.
Sorted Order Books:
bid_book: Sorted in descending order to prioritize the highest bids.
ask_book: Sorted in ascending order to show the lowest asks.


Action Handling: Supports:
'A' (Add): Adds new orders to the book.
'C' (Cancel): Removes orders.
'M' (Modify): Updates existing orders (treated as Cancel + Add).


Robust Output: Generates MBP-10 snapshots after each event, written to mbp_output.csv with precise formatting (e.g., prices to two decimal places).
Error Handling: Skips invalid rows to ensure stability, even with malformed data.

🔍 How It Works

Reading Input: The program uses a custom CSV parser (csv_no_thread.h) to process mbo.csv, extracting fields like ts_recv, ts_event, rtype, action, side, price, size, and order_id.
Updating the Order Book:
Add ('A'): Inserts the order into the appropriate book (bid_book or ask_book) and an unordered_map for fast lookups.
Cancel ('C'): Removes the order from both the book and map.
Modify ('M'): Replaces an existing order with updated details.


Snapshot Generation: After each event, the program creates an MBP-10 snapshot, capturing the top 10 bid and ask levels.
Output Writing: Snapshots are saved to mbp_output.csv with consistent formatting, including timestamps, event metadata, and price/size data.

📊 Sample Output
The output file (mbp_output.csv) contains:



Column Name
Description



index
Event number


ts_recv
Timestamp when the event was received


ts_event
Timestamp when the event occurred


rtype
Record type (set to 10 for MBP-10)


action
Event type (A, C, M)


side
Bid or Ask


order_id
Unique order identifier


bid_px_00 to bid_px_09
Top 10 bid prices


bid_sz_00 to bid_sz_09
Top 10 bid sizes


bid_ct_00 to bid_ct_09
Top 10 bid order counts


ask_px_00 to ask_px_09
Top 10 ask prices


ask_sz_00 to ask_sz_09
Top 10 ask sizes


ask_ct_00 to ask_ct_09
Top 10 ask order counts


💪 Why This Project Stands Out

Stable: Safely skips invalid data rows to prevent crashes.
Fast: Uses unordered_map for O(1) order lookups and map for sorted price levels.
Standardized: Matches the format of official MBP-10 reference files.
Precise: Ensures consistent formatting (e.g., prices like 5.510000000 are output as 5.51).
Extensible: Easily adaptable for additional actions (e.g., Trade or Fill events).

📝 Assumptions

Order IDs are unique and persist across events.
Modify ('M') actions are equivalent to a Cancel followed by an Add.
The depth field is unused in MBO data but included as "0" in MBP output.
Only numeric values are accepted for price, size, and order_id.

📁 File Structure



File
Description



main.cpp
Core logic for processing MBO and generating MBP snapshots


csv_no_thread.h
Lightweight CSV parser for reading input data


mbo.csv
Input file with MBO events


mbp_output.csv
Output file with MBP-10 snapshots


🚀 Getting Started

Install Dependencies:pip install pandas>=1.5.0 matplotlib>=3.5.0 numpy>=1.21.0 seaborn>=0.11.0 jupyterlab>=3.0.0


Compile the Program:Ensure you have a C++ compiler (e.g., g++) installed, then compile main.cpp:g++ main.cpp -o order_book_reconstructor


Prepare Input:Place your mbo.csv file in the same directory as the executable or specify its path.
Run the Program:./order_book_reconstructor


Check Output:The program generates mbp_output.csv with MBP-10 snapshots.

📈 Analyzing Results
You can use Python libraries like pandas and seaborn to analyze or visualize the output. For example:
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

# Load the output
df = pd.read_csv('mbp_output.csv')

# Plot bid and ask prices
sns.lineplot(data=df[['bid_px_00', 'ask_px_00']])
plt.show()

🌟 Enhancements Over Previous Versions



Feature
Improvement



Accurate rtype
Sets rtype = 10 for MBP-10 compliance


Fixed Formatting
Ensures 10 bid + 10 ask levels in correct format


Error Handling
Skips bad rows to avoid crashes


Efficient Structures
Uses unordered_map and map for performance


Precision Control
Formats prices consistently (e.g., 5.51)


📚 Learn More

Understanding Order Books
Market By Order vs. Market By Price

🤝 Contributing
We welcome contributions! To contribute:

Fork the repository.
Create a new branch for your changes.
Submit a pull request with a clear description of your improvements.

Report issues or suggest features via the repository’s issue tracker.
📫 Contact
For questions, feedback, or support, reach out to [Your Name/Email].

Happy coding and exploring the world of financial markets! 🚀
