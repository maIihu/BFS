#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 1;
int dis[MAXN];
int pre[MAXN];
bool vis[MAXN];
vector<int> ds[MAXN];

int n;
int diem_dau, diem_ket_thuc; // dau, cuoi

struct bfs_log {
    char current;
    string neighbors;
    string queueState;
};

vector<bfs_log> logs;

void read_input() {
    ifstream file("D:/Nam3-Ky2/_TriTueNhanTao/BTL/BFS/res/input.txt");
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
            ds[diemDau].push_back(lines[i][j] - 'A');
        }
    }

    diem_dau = lines[n-1][0] - 'A';
    diem_ket_thuc = lines[n-1][2] - 'A';
}

void bfs(int s) {
    queue<int> q;
    q.push(s);
    vis[s] = true;
    bfs_log log;
    log.current = ' ';
    log.neighbors = "";
    log.queueState += char(q.front() + 'A');
    logs.push_back(log);
    while (!q.empty()) {
        bfs_log log;
        int u = q.front();
        log.current = char(u + 'A');
        q.pop();
        if (u == diem_ket_thuc) {
            log.neighbors = "TTKT-DUNG";
            logs.push_back(log);
            return;
        }
        for (auto v : ds[u]) {
            log.neighbors += char(v + 'A');
            log.neighbors += ',';
            if (!vis[v]) {
                dis[v] = dis[u] + 1;
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

void write_output(int ket_thuc) {
    ofstream file("D:/Nam3-Ky2/_TriTueNhanTao/BTL/BFS/res/output.txt");
    if (!file) {
        cerr << "Khong the mo file " << endl;
        return;
    }
    file << string(82, '-') << endl;
    file << "| " << left << setw(25) << "Phat trien trang thai"
         << "| " << setw(25) << "Trang thai ke"
         << "| " << setw(25) << "Danh sach" << "|" << endl;
    file << string(82, '-') << endl;

    for (auto log : logs) {
        file << "| " << left << setw(25) << log.current
             << "| " << setw(25) << log.neighbors
             << "| " << setw(25) << log.queueState << "|\n";
    }
    file << string(82, '-') << endl;
    if (!vis[ket_thuc]) {
        file << "Khong co duong di" << endl;
    }
    else {
        vector<char> path;
        for (int i = pre[ket_thuc]; i != -1; i = pre[i]) {
            path.push_back('A' + i);
        }
        reverse(path.begin(), path.end());
        file << "Duong di: ";
        for (auto x : path)
            file << x << " -> ";
        file << char('A' + ket_thuc) << endl;
    }
    file.close();
    cout << "Chay thanh cong" << endl;
}

int main() {
    memset(vis, false, sizeof(vis));
    memset(dis, 0, sizeof(dis));
    memset(pre, -1, sizeof(pre));
    read_input();
    for (int i = 0; i < n; i++) {
        cout << "Dinh " << char(i + 'A') << " ke voi: ";
        for (auto x : ds[i]) {
            cout << char(x + 'A')  << ' ';
        }
        cout << endl;
    }
    cout << "Diem dau: " << char(diem_dau + 'A') << ' ' << "Diem cuoi: " << char(diem_ket_thuc + 'A') << endl;
    bfs(diem_dau);
    write_output(diem_ket_thuc);
}
