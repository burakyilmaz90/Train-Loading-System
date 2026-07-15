# Train Loading Management System (C)

Trenlere malzeme yükleme ve boşaltma işlemlerini yöneten, çift yönlü bağlı liste (doubly linked list) veri yapısı üzerine kurulmuş, konsol tabanlı bir C uygulaması. Vagon ve malzeme yönetimi, dosyaya kaydetme/dosyadan yükleme özellikleriyle birlikte geliştirilmiştir.

# Problem Tanımı
Bir trenin farklı vagonlarına (Çelik, Alüminyum, Ahşap) ağırlık kapasitesi gözetilerek malzeme yüklenmesini ve boşaltılmasını simüle eden bir yönetim sistemi.

# Özellikler (Ana Menü)
1. Dosyadan tren durumunu yükleme
2. Trenin başından itibaren otomatik malzeme yükleme
3. Belirli bir vagona malzeme yükleme
4. Trenin sonundan itibaren otomatik malzeme boşaltma
5. Belirli bir vagondan malzeme boşaltma
6. Tren durumunu görüntüleme
7. Malzeme durumunu görüntüleme
8. Treni tamamen boşaltma
9. Tren durumunu dosyaya kaydetme
10. Çıkış

# Mimari ve Veri Yapıları
`include/` (header) ve `src/` (implementasyon) olarak modüler yapı. **Train**, **Vagon** (çift yönlü bağlı liste), **MaterialType/LoadedMaterial** yapıları kullanılmıştır.

# Kullanılan Teknolojiler
- Dil: C
- Veri Yapıları: Çift yönlü bağlı liste (Doubly Linked List)
- Bellek Yönetimi: Dinamik bellek tahsisi (malloc/free)
- Dosya İşlemleri: Tren durumunun dosyaya yazılıp okunması

# Derleme ve Çalıştırma
\`\`\`bash
gcc src/*.c -Iinclude -o train_system
./train_system
\`\`\`

---
Bu proje, Fatih Sultan Mehmet Vakıf Üniversitesi Yazılım Mühendisliği bölümü kapsamında geliştirilmiştir.Ekip çalışmasıdır.
