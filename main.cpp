#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 1;

int d[MAXN]; // kc
int pre[MAXN]; // diem truoc
bool vis[MAXN]; // den tham
vector<int> g[MAXN]; // ds ke ( dinh - ke )

int n;
int st, ed; // dau, cuoi

struct BFSLog {
    char current;
    string neighbors;
    string queueState;
};

vector<BFSLog> logs;

void read_input() {
    ifstream file("D:/Nam3-Ky2/_TriTueNhanTao/BTL/BFS/input.txt");
    if (!file.is_open()) {
        cout << "Khong mo duoc file" << endl;
        return;
    }
    vector<string> lines;
    string line;
    while (getline(file, line))
        lines.push_back(line);
    file.close();
    n = lines.size();

    for (int i = 0; i < n-1; i++) {
        int diemDau = lines[i][0] - 'A';
        for (int j = 1; j < lines[i].size(); j++) {
            if (lines[i][j] == ' ' || lines[i][j] == '\n') continue;
            g[diemDau].push_back(lines[i][j] - 'A');
        }
    }

    st = lines[n-1][0] - 'A';
    ed = lines[n-1][2] - 'A';
}

void bfs(int s) {
    memset(vis, false, sizeof(vis));
    memset(d, 0, sizeof(d));
    memset(pre, -1, sizeof(pre));
    queue<int> q;
    q.push(s);
    vis[s] = true;

    while (!q.empty()) {
        BFSLog log;
        int u = q.front();
        log.current = char(u + 'A');
        q.pop();
        if (u == ed) {
            log.neighbors = "TTKT-DUNG";
            logs.push_back(log);
            return;
        }
        for (auto v : g[u]) {
            log.neighbors += char(v + 'A');
            log.neighbors += ',';
            if (!vis[v]) {
                d[v] = d[u] + 1;
                pre[v] = u;
                q.push(v);
                vis[v] = true;
            }
        }
        if (!log.neighbors.empty()) log.neighbors.pop_back();
        queue<int> temp = q;
        while (!temp.empty()) {
            log.queueState += char(temp.front() + 'A');
            log.queueState += ',';
            temp.pop();
        }
        if (!log.queueState.empty()) log.queueState.pop_back();
        logs.push_back(log);
    }
}

void write_output(int e, string file_name = "D:/Nam3-Ky2/_TriTueNhanTao/BTL/BFS/output.txt") {
    ofstream file(file_name);
    if (!file) {
        cerr << "Khong the mo file " << file_name << endl;
        return;
    }
    file << string(82, '-') << endl;
    file << "| " << left << setw(25) << "Phat trien trang thai"
         << "| " << setw(25) << "Trang thai ke"
         << "| " << setw(25) << "Danh sach" << "|\n";
    file << string(82, '-') << endl;

    for (auto log : logs) {
        file << "| " << left << setw(25) << log.current
             << "| " << setw(25) << log.neighbors
             << "| " << setw(25) << log.queueState << "|\n";
        file << string(82, '-') << endl;
    }

    if (!vis[e]) {
        file << "Khong co duong di" << endl;
    } else {
        vector<char> path;
        for (int i = pre[e]; i != -1; i = pre[i]) {
            path.push_back('A' + i);
        }
        reverse(path.begin(), path.end());
        file << "Duong di: ";
        for (auto x : path)
            file << x << " -> ";
        file << char('A' + e) << endl;
    }
    file.close();
    cout << "Da in ra file " + file_name << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    read_input();
    for (int i = 0; i < n; i++) {
        cout << "Dinh " << char(i + 'A') << " ke voi: ";
        for (auto x : g[i]) {
            cout << char(x + 'A')  << ' ';
        }
        cout << endl;
    }
    cout << "Diem dau: " << char(st + 'A') << ' ' << "Diem cuoi: " << char(ed + 'A') << endl;
    bfs(st);

    write_output(ed);
}
