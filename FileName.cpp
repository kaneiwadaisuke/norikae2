#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <limits>

using namespace std;

class Station;

class Connection {
public:
    Station* station;
    int distance;
    string lineName;

    Connection(Station* s, int d, string l) : station(s), distance(d), lineName(l) {}
};

class Station {
public:
    string name;
    vector<Connection> connections;

    Station(string n) : name(n) {}

    void addConnection(Station* station, int distance, string lineName) {
        connections.emplace_back(station, distance, lineName);
    }
};

class SubwaySystem {
public:
    unordered_map<string, Station*> stations;

    void addStation(string name) {
        stations[name] = new Station(name);
    }

    void addConnection(string from, string to, int distance, string lineName) {
        stations[from]->addConnection(stations[to], distance, lineName);
        stations[to]->addConnection(stations[from], distance, lineName);
    }

    void findShortestRoute(string start, string destination) {
        unordered_map<string, int> distances;
        unordered_map<string, pair<string, string>> previous; 
        for (auto& station : stations) {
            distances[station.first] = numeric_limits<int>::max();
        }
        distances[start] = 0;

        auto compare = [&distances](string left, string right) { return distances[left] > distances[right]; };
        priority_queue<string, vector<string>, decltype(compare)> queue(compare);

        queue.push(start);

        while (!queue.empty()) {
            string current = queue.top();
            queue.pop();

            if (current == destination) {
                break;
            }

            for (auto& neighbor : stations[current]->connections) {
                int alt = distances[current] + neighbor.distance;
                if (alt < distances[neighbor.station->name]) {
                    distances[neighbor.station->name] = alt;
                    previous[neighbor.station->name] = { current, neighbor.lineName };
                    queue.push(neighbor.station->name);
                }
            }
        }

        printRoute(previous, start, destination);
    }

private:
    void printRoute(unordered_map<string, pair<string, string>>& previous, string start, string destination) {
        vector<string> path;
        vector<string> lines;
        for (string at = destination; at != start; at = previous[at].first) {
            path.push_back(at);
            lines.push_back(previous[at].second);
        }
        path.push_back(start);
        reverse(path.begin(), path.end());
        reverse(lines.begin(), lines.end());

        if (path[0] == start) {
            cout << start << "����" << destination << "�܂�" << ": " << endl;
            string lastLine = "";
            for (size_t i = 0; i < path.size(); ++i) {
                cout << path[i];
                if (i < lines.size()) {
                    if (lines[i] != lastLine) {
                        cout << " (" << lines[i] << ")";
                        lastLine = lines[i];
                    }
                }
                if (i < path.size() - 1) {
                    cout << " -> ";
                }
            }
            cout << endl;
        }
        else {
            cout << start << "����" << destination << "�܂ł�" << "���[�g��������܂���ł����B" << endl;
        }
    }
};

int main() {
    SubwaySystem system;

    // �w�̒ǉ�
   
    //�R���
    system.addStation("����");
    system.addStation("�L�y��");
    system.addStation("�V��");
    system.addStation("�l����");
    system.addStation("���փQ�[�g�E�F�C");
    system.addStation("�c��");
    system.addStation("���");
    system.addStation("�i��");
    system.addStation("�ܔ��c");
    system.addStation("�ڍ�");
    system.addStation("�b���");
    system.addStation("�a�J");
    system.addStation("���h");
    system.addStation("��X��");
    system.addStation("�V�h");
    system.addStation("�V��v��");
    system.addStation("���c�n��");
    system.addStation("�ڔ�");
    system.addStation("�r��");
    system.addStation("���");
    system.addStation("����");
    system.addStation("�");
    system.addStation("�c�[");
    system.addStation("�����闢");
    system.addStation("���闢");
    system.addStation("��J");
    system.addStation("���");
    system.addStation("��k��");
    system.addStation("�H�t��");
    system.addStation("�_�c");
   
    //���l���k��
    
    system.addStation("��䒬");
    system.addStation("��X");
    system.addStation("���c");
    system.addStation("�ԉH");
    system.addStation("���\��");
    system.addStation("���q");
    system.addStation("�㒆��");

    //������
    system.addStation("�n��");
    system.addStation("�����{��");
    system.addStation("�󑐋�");
    system.addStation("����");
    system.addStation("�ю���");
    system.addStation("�T��");
    system.addStation("����");
    system.addStation("�V����");
    system.addStation("����");
    
    //������
    system.addStation("�����̐�");
    system.addStation("������");
    system.addStation("�s���J");
    system.addStation("�ѓc��");
    system.addStation("�l�c�J");
    system.addStation("�M�Z��");
    system.addStation("��ʃ��J");
    system.addStation("��v��");
    system.addStation("������");
    system.addStation("����");
    system.addStation("���~��");
    system.addStation("�������J");
    system.addStation("���E");
    system.addStation("�����E");
    system.addStation("�g�ˎ�");
    system.addStation("�O��");
  
    //���̑�
    system.addStation("���ԏM�n");
    system.addStation("�k�ԉH");
    system.addStation("�\��");
    system.addStation("��");
    system.addStation("���v");
    system.addStation("�k��Z");
    system.addStation("���Z");
    system.addStation("�O�͓�");
    system.addStation("����");
    system.addStation("�T�L");
    system.addStation("����");
    system.addStation("�����");
    system.addStation("�����x");
    system.addStation("�z����");
    system.addStation("����");
    system.addStation("�V�؏�");
    system.addStation("�����ՊC����");

    // �ڑ��̒ǉ� (���̋����ƘH�����Őݒ�)
    
    // �R��� (Yamanote Line)
    system.addConnection("����", "�L�y��", 2, "�R���");
    system.addConnection("�L�y��", "�V��", 2, "�R���");
    system.addConnection("�V��", "�l����", 2, "�R���");
    system.addConnection("�l����", "���փQ�[�g�E�F�C", 2, "�R���");
    system.addConnection("���փQ�[�g�E�F�C", "�c��", 2, "�R���");
    system.addConnection("�c��", "���", 2, "�R���");
    system.addConnection("���", "�i��", 3, "�R���");
    system.addConnection("�i��", "�ܔ��c", 2, "�R���");
    system.addConnection("�ܔ��c", "�ڍ�", 2, "�R���");
    system.addConnection("�ڍ�", "�b���", 3, "�R���");
    system.addConnection("�b���", "�a�J", 2, "�R���");
    system.addConnection("�a�J", "���h", 2, "�R���");
    system.addConnection("���h", "��X��", 2, "�R���");
    system.addConnection("��X��", "�V�h", 2, "�R���");
    system.addConnection("�V�h", "�V��v��", 2, "�R���");
    system.addConnection("�V��v��", "���c�n��", 2, "�R���");
    system.addConnection("���c�n��", "�ڔ�", 2, "�R���");
    system.addConnection("�ڔ�", "�r��", 3, "�R���");
    system.addConnection("�r��", "���", 2, "�R���");
    system.addConnection("���", "����", 2, "�R���");
    system.addConnection("����", "�", 2, "�R���");
    system.addConnection("�", "�c�[", 2, "�R���");
    system.addConnection("�c�[", "�����闢", 2, "�R���");
    system.addConnection("�����闢", "���闢", 1, "�R���");
    system.addConnection("���闢", "��J", 2, "�R���");
    system.addConnection("��J", "���", 2, "�R���");
    system.addConnection("���", "��k��", 2, "�R���");
    system.addConnection("��k��", "�H�t��", 2, "�R���");
    system.addConnection("�H�t��", "�_�c", 2, "�R���");
    system.addConnection("�_�c", "����", 1, "�R���");

    // ���l���k�� (Keihin-Tohoku Line)
    system.addConnection("��䒬", "��X", 2, "���l���k��");
    system.addConnection("��X", "���c", 2, "���l���k��");
    system.addConnection("���c", "�i��", 2, "���l���k��");
    system.addConnection("�ԉH", "���\��", 3, "���l���k��");
    system.addConnection("���\��", "���q", 3, "���l���k��");
    system.addConnection("���q", "�㒆��", 2, "���l���k��");
    system.addConnection("���q", "�㒆��", 3, "���l���k��");
   
    // ������ (Sobu Line)
    system.addConnection("�n��", "�����{��", 3, "����������");
    system.addConnection("�����{��", "����", 4, "����������");
    system.addConnection("�n��", "�ю���", 5, "����������");
    system.addConnection("�V����", "�ю���", 5, "����������");
    system.addConnection("�󑐋�", "����", 2, "������");
    system.addConnection("����", "�ю���", 2, "������");
    system.addConnection("�ю���", "�T��", 2, "������");
    system.addConnection("�T��", "����", 3, "������");
    system.addConnection("����", "�V����", 2, "������");
    system.addConnection("�V����", "����", 2, "������");

    // ������ (Chuo Line)
    system.addConnection("�����̐�", "������", 2, "������");
    system.addConnection("������", "�s���J", 2, "������");
    system.addConnection("�s���J", "�ѓc��", 2, "������");
    system.addConnection("�ѓc��", "�l�c�J", 2, "������");
    system.addConnection("�l�c�J", "�M�Z��", 2, "������");
    system.addConnection("�M�Z��", "��ʃ��J", 2, "������");
    system.addConnection("�M�Z��", "��X��", 1, "������");
    system.addConnection("��v��", "�V�h", 2, "������");
    system.addConnection("��ʃ��J", "��v��", 1, "������");
    system.addConnection("��v��", "������", 1, "������");
    system.addConnection("������", "����", 1, "������");
    system.addConnection("����", "���~��", 1, "������");
    system.addConnection("���~��", "�������J", 1, "������");
    system.addConnection("�������J", "���E", 1, "������");
    system.addConnection("���E", "�����E", 1, "������");
    system.addConnection("�����E", "�g�ˎ�", 1, "������");
    system.addConnection("�g�ˎ�", "�O��", 1, "������");

    // ���������� (Chuo Line)
    system.addConnection("�����̐�", "�l�c�J", 2, "����������");
    system.addConnection("�_�c", "�����̐�", 2, "����������");
    system.addConnection("�l�c�J", "�V�h", 2, "����������");
    system.addConnection("����", "�_�c", 1, "����������");
    // ���̑� (Other Stations)
    //�鋞��
    system.addConnection("���ԏM�n", "�k�ԉH", 2, "�鋞��");
    system.addConnection("�ԉH", "�k�ԉH", 2, "�鋞��");
    system.addConnection("�ԉH", "�\��", 2, "�鋞��");
    system.addConnection("�\��", "��", 2, "�鋞��");
    system.addConnection("��", "�r��", 2, "�鋞��");
    system.addConnection("���", "�a�J", 4, "�鋞��");
    system.addConnection("�a�J", "�V�h", 4, "�鋞��");
    system.addConnection("�V�h", "�r��", 5, "�鋞��");

    system.addConnection("���v", "�k��Z", 2, "���̑�");
    system.addConnection("�k��Z", "���Z", 2, "���̑�");
    system.addConnection("���Z", "�O�͓�", 2, "���̑�");
    system.addConnection("�O�͓�", "����", 2, "���̑�");
    system.addConnection("����", "�T�L", 2, "���̑�");
    system.addConnection("�T�L", "����", 2, "���̑�");
    system.addConnection("����", "�����", 2, "���̑�");
    system.addConnection("�����", "�����x", 2, "���̑�");
    system.addConnection("�����x", "�z����", 2, "���̑�");
    system.addConnection("�z����", "����", 2, "���̑�");
    system.addConnection("����", "�V�؏�", 2, "���̑�");
    system.addConnection("�V�؏�", "�����ՊC����", 2, "���̑�");


    // ���[�U�[����
    string startStation, endStation;
    cout << "��ԉw����͂��ĉ�����: ";
    cin >> startStation;
    cout << "�~�ԉw����͂��Ă�������: ";
    cin >> endStation;

    // �o�H����
    system.findShortestRoute(startStation, endStation);

    return 0;
}
