# DP-Week2-5224600048-Shabri Afrizal Sutrisno

## Task 2 - Develop Your Own Core Loop

### Step 1 - Core Loop (Based on Pretest Game)

1. Player memilih kartu dari hand untuk dimainkan atau dibuang.
2. System mengevaluasi kombinasi kartu dan menentukan hand rank.
3. Reward atau penalty diberikan dalam bentuk score gain, cash gain, atau kehilangan peluang.
4. Game state diperbarui: total score, target progression, kartu di hand, dan kondisi akhir ronde.
5. Cek kondisi menang atau kalah.
6. Repeat.

### Step 2 - Invariants

#### 1) Langkah yang tidak boleh berubah urutan

- Player action harus terjadi sebelum evaluasi sistem.
- Evaluasi sistem harus terjadi sebelum reward atau penalty.
- Reward atau penalty harus terjadi sebelum update state.
- Update state harus terjadi sebelum pengecekan akhir game.

#### 2) Komponen yang harus selalu ada

- Komponen input aksi pemain.
- Komponen evaluasi kartu dan skor.
- Komponen reward or penalty.
- Komponen penyimpanan dan pembaruan game state.
- Komponen kontrol loop sesi permainan.

#### 3) Yang rusak jika urutan berubah

- Jika evaluasi dilakukan sebelum player action, sistem akan membaca data pilihan yang belum ada.
- Jika state di-update sebelum reward dihitung, score dan target bisa tidak sinkron.
- Jika end-check dilakukan terlalu awal, game bisa berhenti sebelum hasil aksi diproses.
- Jika reward diberikan sebelum evaluasi, angka reward menjadi acak dan tidak valid.

### Step 3 - Mutable Elements

1. Score formula.
   Mutable karena bisa diubah untuk balancing tanpa mengubah struktur loop utama.
2. Target score progression (contoh 200, 400, 800).
   Mutable karena level scaling dapat disesuaikan berdasarkan difficulty.
3. Cash reward amount setelah target tercapai.
   Mutable karena ekonomi game bisa dituning agar pacing lebih stabil.
4. Max round atau batas durasi sesi.
   Mutable karena dapat disesuaikan untuk mode cepat atau mode panjang.

### Step 4 - C++ Core Loop Skeleton

Implementasi skeleton disediakan pada folder Task2, dengan pemisahan fase di dalam class RunSession:

- Player action phase
- System evaluation phase
- Reward or penalty phase
- Update state phase

Semua fase dipanggil berurutan dalam loop utama dan tidak diletakkan langsung di main.

## Reflection (300-400 words)

Invariant structure dari game saya adalah urutan tetap antara aksi pemain, evaluasi sistem, pemberian hasil, lalu pembaruan state. Urutan ini adalah fondasi karena game berbasis keputusan kartu. Pemain harus melakukan pilihan dulu, baru sistem bisa mengevaluasi kombinasi. Setelah evaluasi selesai, game memberikan konsekuensi berupa score atau reward lain. Langkah terakhir adalah update state untuk menyimpan hasil ronde dan mempersiapkan iterasi berikutnya. Selama fondasi ini dipertahankan, isi game bisa berkembang tanpa membuat arsitektur rusak.

Bagian mutable dari game saya terutama ada pada parameter gameplay, bukan struktur. Contohnya score formula, target progression, reward cash, jumlah kartu awal, dan batas ronde. Nilai-nilai ini bisa diubah untuk balancing, tuning difficulty, atau menyesuaikan pengalaman pemain. Saat saya ingin game terasa lebih menantang, saya dapat menaikkan target score atau menurunkan reward. Saat saya ingin game lebih cepat, saya bisa mengurangi max round. Semua perubahan itu tidak menuntut saya mengubah kerangka loop, sehingga desain tetap bersih.

Jika saya ingin menambah fitur baru, kelas yang paling mungkin berubah adalah kelas fase terkait, terutama ScoringSystem, RewardSystem, atau RunSession. Misalnya saya menambah sistem combo multiplier, maka ScoringSystem akan berubah untuk menghitung bonus baru, dan mungkin RewardSystem ikut berubah jika combo memberi cash tambahan. RunSession biasanya hanya berubah jika ada fase baru yang benar-benar dibutuhkan oleh struktur. Dengan pendekatan ini, perubahan fitur tetap lokal dan tidak menyebar ke seluruh program.

Jika urutan loop diubah, masalah utama adalah inkonsistensi data dan keputusan yang tidak valid. Contoh paling jelas: jika update state dilakukan sebelum reward dihitung, state akan mencatat kondisi yang belum final. Jika end-check dilakukan sebelum evaluasi selesai, game bisa berhenti walau aksi pemain belum diproses. Jika reward diberikan sebelum evaluasi, sistem tidak punya dasar objektif untuk menentukan hasil. Dampaknya bukan hanya bug teknis, tetapi juga pengalaman pemain yang terasa tidak adil, karena game tampak memberi hasil tanpa alasan yang jelas.
