#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <iomanip>
#include <algorithm>
#include "csv_no_thread.h"

struct Order {
    double price;
    int size;
    char side;
};

std::unordered_map<uint64_t, Order> order_map;
std::map<double, int, std::greater<double>> bid_book;
std::map<double, int> ask_book;

bool is_numeric(const std::string& s) {
    return !s.empty() && std::all_of(s.begin(), s.end(), [](char c) {
        return std::isdigit(c) || c == '.' || c == '-';
    });
}

template <typename BookType>
void remove_from_book(BookType& book, double price, int size) {
    book[price] -= size;
    if (book[price] <= 0) {
        book.erase(price);
    }
}

void update_order_book(char action, char side, uint64_t order_id, double price, int size) {
    if (action == 'A') {
        order_map[order_id] = {price, size, side};
        if (side == 'B') bid_book[price] += size;
        else if (side == 'A') ask_book[price] += size;
    } else if (action == 'C') {
        if (order_map.count(order_id)) {
            auto& ord = order_map[order_id];
            if (ord.side == 'B') remove_from_book(bid_book, ord.price, ord.size);
            else if (ord.side == 'A') remove_from_book(ask_book, ord.price, ord.size);
            order_map.erase(order_id);
        }
    } else if (action == 'M') {
        update_order_book('C', side, order_id, 0, 0);
        update_order_book('A', side, order_id, price, size);
    }
}

void dump_mbp(std::ofstream& out, int index,
              const std::string& ts_recv, const std::string& ts_event,
              const std::string& rtype, const std::string& publisher_id, const std::string& instrument_id,
              const std::string& action, const std::string& side, const std::string& depth,
              const std::string& price, const std::string& size, const std::string& flags,
              const std::string& ts_in_delta, const std::string& sequence,
              const std::string& symbol, const std::string& order_id) {

    out << index << "," << ts_recv << "," << ts_event << "," << rtype << "," << publisher_id << "," << instrument_id << ","
        << action << "," << side << "," << depth << "," << price << "," << size << "," << flags << ","
        << ts_in_delta << "," << sequence << ",";

    auto bid_it = bid_book.begin();
    auto ask_it = ask_book.begin();

    for (int i = 0; i < 10; ++i) {
        if (bid_it != bid_book.end()) {
            out << std::fixed << std::setprecision(2) << bid_it->first << "," << bid_it->second << ",1,";
            ++bid_it;
        } else {
            out << ",0,0,";
        }

        if (ask_it != ask_book.end()) {
            out << std::fixed << std::setprecision(2) << ask_it->first << "," << ask_it->second << ",1,";
            ++ask_it;
        } else {
            out << ",0,0,";
        }
    }

    out << symbol << "," << order_id << "\n";
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " mbo.csv\n";
        return 1;
    }

    CSVReader reader(argv[1]);
    CSVRow row;

    std::ofstream out("mbp_output.csv");
    out << "index,ts_recv,ts_event,rtype,publisher_id,instrument_id,action,side,depth,price,size,flags,ts_in_delta,sequence,"
        << "bid_px_00,bid_sz_00,bid_ct_00,ask_px_00,ask_sz_00,ask_ct_00,"
        << "bid_px_01,bid_sz_01,bid_ct_01,ask_px_01,ask_sz_01,ask_ct_01,"
        << "bid_px_02,bid_sz_02,bid_ct_02,ask_px_02,ask_sz_02,ask_ct_02,"
        << "bid_px_03,bid_sz_03,bid_ct_03,ask_px_03,ask_sz_03,ask_ct_03,"
        << "bid_px_04,bid_sz_04,bid_ct_04,ask_px_04,ask_sz_04,ask_ct_04,"
        << "bid_px_05,bid_sz_05,bid_ct_05,ask_px_05,ask_sz_05,ask_ct_05,"
        << "bid_px_06,bid_sz_06,bid_ct_06,ask_px_06,ask_sz_06,ask_ct_06,"
        << "bid_px_07,bid_sz_07,bid_ct_07,ask_px_07,ask_sz_07,ask_ct_07,"
        << "bid_px_08,bid_sz_08,bid_ct_08,ask_px_08,ask_sz_08,ask_ct_08,"
        << "bid_px_09,bid_sz_09,bid_ct_09,ask_px_09,ask_sz_09,ask_ct_09,"
        << "symbol,order_id\n";

    reader.read_row(row); // Skip header
    int index = 0;

    while (reader.read_row(row)) {
        if (row.size() < 15) continue;

        std::string ts_recv = row[0];
        std::string ts_event = row[1];
        std::string rtype = "10"; // override to match desired output
        std::string publisher_id = row[3];
        std::string instrument_id = row[4];
        std::string action = row[5];
        std::string side = row[6];
        std::string price = row[7];
        std::string size = row[8];
        std::string depth = "0"; // override to 0
        std::string order_id = row[10];
        std::string flags = row[11];
        std::string ts_in_delta = row[12];
        std::string sequence = row[13];
        std::string symbol = row[14];

        if (action.empty() || side.empty() || !is_numeric(price) || !is_numeric(size) || !is_numeric(order_id))
            continue;

        update_order_book(action[0], side[0], std::stoull(order_id), std::stod(price), std::stoi(size));

        dump_mbp(out, index++, ts_event, ts_event, rtype, publisher_id, instrument_id,
                 action, side, depth, price, size, flags, ts_in_delta, sequence,
                 symbol, order_id);
    }

    reader.close();
    out.close();
    std::cout << "✅ mbp_output.csv generated successfully.\n";
    return 0;
}