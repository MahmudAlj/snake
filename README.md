# Yılan Oyunu (Raylib, C++)

Küçük ama genişletilebilir bir **Snake / Yılan** oyunu. Oyun; `raylib` ve `raymath` kullanır, elma (texture) yeme, büyüme, skor, kuyruk/kenar çarpışmaları ve klavye ile kontrolü içerir. Kaynak kodda iki sürüm bulunur: `snake.cpp` (daha güncel ve sınır kontrolleri düzeltilmiş) ve `yilann.cpp` (ilk sürüm).

> Bu README, depodaki `snake.cpp` ve `yilann.cpp` dosyalarına göre hazırlanmıştır.   
> Kaynaklar: snake.cpp, yilann.cpp

---

## Özellikler

- Raylib ile pencereli oyun döngüsü
- Elma/food oluşturma ve **rastgele** konumlandırma (yılan gövdesine düşmeyecek şekilde)
- Elma yeme → yılanın büyümesi, **skor artışı**
- **Kuyruk** ve **kenar** çarpışma kontrolleri
- 0.1 sn güncelleme aralığı için basit zamanlayıcı (`eventTriggered`)
- Basit skor yazımı ve oyun alanı çerçevesi

`snake.cpp`’de kenar çarpışmaları, **ızgara boyutu (`noktsayimi`)** üzerinden doğru şekilde kontrol edilir. `yilann.cpp`’de eski bir varyantta hatalı olarak hücre pikseli (`noktaboyutu`) ile karşılaştırma yapılmıştı; bu sürümde düzeltilmiştir.

## Kurulum

1. **Raylib** ve **raymath** başlık/dinamiklerini kurun.
   - Windows: vcpkg veya raylib releases
   - Linux: `sudo apt install libraylib-dev` (dağıtıma göre değişebilir) veya kaynak koddan derleyin
   - macOS: `brew install raylib`
2. Projeyi **Visual Studio** (sağlanan `yilann.sln`) ile ya da komut satırından derleyebilirsiniz.


## Derleme ve Çalıştırma

### Windows (MSVC / Visual Studio)

- `yilann.sln` çözüm dosyasını açın, `Release x64` seçin ve **Build** edin.
- Raylib’i projenize **Include** ve **Library** yolları olarak ekleyin; `raylib.lib`’i linkleyin.
- Çalıştırmadan önce **texture dosyasının yolu**nun doğru olduğundan emin olun (aşağıya bakın).

### Windows (MinGW-w64)

```bash
g++ snake.cpp -o snake ^
  -I<raylib>\include -L<raylib>\lib ^
  -lraylib -lopengl32 -lgdi32 -lwinmm
.\snake.exe
```

> `<raylib>` klasör yolunu kendi ortamınıza göre değiştirin.

### Linux (gcc/clang)

```bash
g++ snake.cpp -o snake -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
./snake
```

### macOS (clang/Homebrew)

```bash
brew install raylib
clang++ snake.cpp -o snake \
  -I/usr/local/include -L/usr/local/lib -lraylib \
  -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
./snake
```


## Oynanış

- Yılan sürekli son girilen yönde hareket eder.
- Elmayı yediğinizde skor **+1** olur ve yılan bir parça büyür.
- **Duvara** veya **kendi kuyruğunuza** çarparsanız **Game Over** olur, yılan resetlenir ve skor sıfırlanır.


## Kontroller

- **Yukarı**: `↑` (yön vektörü `{0, -1}`)
- **Aşağı**: `↓` (yön vektörü `{0, 1}`)
- **Sol**: `←` (yön vektörü `{-1, 0}`)
- **Sağ**: `→` (yön vektörü `{1, 0}`)


## Yapılandırma / Ayarlar

Aşağıdaki sabitler oyun alanını ve görünümü kontrol eder:

- `noktaboyutu` — Hücre piksel boyutu (varsayılan **30 px**)
- `noktsayimi` — Izgara boyutu / satır-sütun sayısı (varsayılan **25**)
- `offset` — Oyun alanının penceredeki iç boşluğu (varsayılan **75 px**)

> Bu değerler hem pencere boyutunu hem de çizimleri etkiler. Örn: pencere genişliği `2*offset + noktaboyutu * noktsayimi` formülüyle hesaplanır.


## Proje Yapısı

```
.
├─ snake.cpp        # Güncel sürüm (kenar kontrolü düzeltildi)
├─ yilann.cpp       # İlk sürüm
├─ yilann.sln       # Visual Studio çözümü
└─ assets/
   └─ apple.png     # Elma için texture (dosyayı siz eklemelisiniz)
```

> **Texture yolu:**  
> - `yilann.cpp`: `"graph/gomb1.png"` yolunu bekliyor (varsa).  
> - `snake.cpp`: `"path/to/your/image.png"` olarak placeholder geçilmiş; gerçek dosya yolunu siz verin.  
> Öneri: `assets/apple.png` kullanın ve kodu buna göre düzenleyin:

```cpp
Image image = LoadImage("assets/apple.png");
Texture2D texture = LoadTextureFromImage(image);
```


## Sık Karşılaşılan Sorunlar

- **Texture bulunamıyor / resim yüklenemedi:** Dosya yolu yanlış veya dosya eksik. Çalışma dizininizin **exe** ile aynı klasör olduğunu ve `assets/apple.png` dosyasının gerçekten var olduğunu kontrol edin. `snake.cpp` bu durumda basit bir hata mesajı da yazdırır.
- **Kenar çarpışması hemen game over yapıyor:** Izgara (`noktsayimi`) ve başlangıç konumları uyumlu olmalı. `snake.cpp`’de kontrol: `x >= noktsayimi || x < 0` ve `y >= noktsayimi || y < 0` şeklindedir.
- **FPS / hız çok hızlı veya yavaş:** `eventTriggered(0.1)` ile adım aralığını değiştirin. Örn: daha hızlı için `0.08`, daha yavaş için `0.12` gibi.


## Geliştirme Notları ve Yol Haritası

- Ses efektleri (elma yeme, game over)
- Oyun içi **pause** tuşu ve başlangıç ekranı
- Skor tablosu / en yüksek skor kaydı
- Farklı güçlendiriciler, duvarlar ve seviyeler
- Dokunmatik/joystick desteği

Katkılar ve öneriler PR olarak memnuniyetle kabul edilir.


