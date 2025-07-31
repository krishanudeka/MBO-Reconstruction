import pandas as pd
import matplotlib.pyplot as plt

# Load the files
official_mbp = pd.read_csv("mbp.csv")
generated_mbp = pd.read_csv("mbp_output.csv")

# Convert timestamps to datetime
official_mbp['ts_event'] = pd.to_datetime(official_mbp['ts_event'])
generated_mbp['ts_event'] = pd.to_datetime(generated_mbp['ts_event'])

# Sort by event time
official_mbp = official_mbp.sort_values('ts_event')
generated_mbp = generated_mbp.sort_values('ts_event')

# Extract Top-of-Book (Level 1)
def extract_top_book(df):
    return pd.DataFrame({
        'ts_event': df['ts_event'],
        'bid_px': df['bid_px_00'],
        'bid_sz': df['bid_sz_00'],
        'ask_px': df['ask_px_00'],
        'ask_sz': df['ask_sz_00']
    })

official_top = extract_top_book(official_mbp)
generated_top = extract_top_book(generated_mbp)

# Plot Bid Price Comparison
plt.figure(figsize=(14, 6))
plt.plot(official_top['ts_event'], official_top['bid_px'], label="Official Bid Price", marker='o')
plt.plot(generated_top['ts_event'], generated_top['bid_px'], label="Generated Bid Price", marker='x')
plt.title("Top-of-Book Bid Price Comparison")
plt.xlabel("Time")
plt.ylabel("Bid Price")
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.show()

# Plot Ask Price Comparison
plt.figure(figsize=(14, 6))
plt.plot(official_top['ts_event'], official_top['ask_px'], label="Official Ask Price", marker='o')
plt.plot(generated_top['ts_event'], generated_top['ask_px'], label="Generated Ask Price", marker='x')
plt.title("Top-of-Book Ask Price Comparison")
plt.xlabel("Time")
plt.ylabel("Ask Price")
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.show()

# Plot Bid Size Comparison
plt.figure(figsize=(14, 4))
plt.plot(official_top['ts_event'], official_top['bid_sz'], label="Official Bid Size", marker='o')
plt.plot(generated_top['ts_event'], generated_top['bid_sz'], label="Generated Bid Size", marker='x')
plt.title("Top-of-Book Bid Size Comparison")
plt.xlabel("Time")
plt.ylabel("Bid Size")
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.show()

# Plot Ask Size Comparison
plt.figure(figsize=(14, 4))
plt.plot(official_top['ts_event'], official_top['ask_sz'], label="Official Ask Size", marker='o')
plt.plot(generated_top['ts_event'], generated_top['ask_sz'], label="Generated Ask Size", marker='x')
plt.title("Top-of-Book Ask Size Comparison")
plt.xlabel("Time")
plt.ylabel("Ask Size")
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.show()