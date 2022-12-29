#include <iostream>
#include <dirent.h>
#include <sys/stat.h>
using namespace std;

string jarak(int N) {
	string hasil = "";
	for(int i = 0; i <= N; i++) {
        hasil = hasil + "    ";
	}
	return hasil;
}

void jelajahDirektori(string path, int n) {
    DIR *dir;
    struct dirent *entry;
    struct stat statbuf;

    if ((dir = opendir(path.c_str())) == NULL) {
        cerr << "Eror ketika membuka " << path << endl;
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        string namaEntry = entry->d_name;
        // Lewati direktori saat ini dan direktori parent
        if (namaEntry == "." || namaEntry == "..") {
        	continue;
		}

        string pathSaatIni = path + "/" + namaEntry;
        stat(pathSaatIni.c_str(), &statbuf);

        if (S_ISDIR(statbuf.st_mode)) {
            // Menampilkan folder
            cout << jarak(n) << "- "  << namaEntry << "/" << endl;
            jelajahDirektori(pathSaatIni, n+1);
        } else {
            // Menampilkan file
            cout << jarak(n) << "* " << namaEntry << endl;
        }
    }
    n = 0;
    closedir(dir);
}

int main() {
	cout << "Masukkan path: ";
    string path;  
    getline(cin >> ws, path); // Start
    cout << endl << endl;
    
    cout << "+ " << path << endl;
    jelajahDirektori(path, 0);
    return 0;
}
