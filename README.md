# Secure-Hash-Algorithm-1
SHA-1 Algorithm.

*union Plaintext - 512 bitlik bloku barindirmak icindir.512 bit metine
hem 64 adet 8bit hem de 16 adet 32 bit seklinde erismeyi saglar.

*padding() - Eger bos alan varsa verilen metnin sonuna 1 adet 1 ve blok sonuna
kadar 0 ekliyor.

*addLength() - verilen blokun son 64 bitlik alanina tum mesajin boyutunu ekliyor.
bu fonksiyon sadece son blok icin kullanilir.

*extendMessage() - Verilen 16 adet 32 bitlik veriyi genisleterek 80 adet 32 bitlik 
veriye donusturuyor.

*func() - Her 20 dongude bir fonksiyon degerinin degismesi gerekiyor.Verilen 
i degerine gore dongu araligini belirleyerek farkli sonuclar donduruyor.

*hashBlock() - aldigi metni genilettikten sonra esas dongu icerisinde A,B,C,D,E 
degerlerini hesablar ve hash degiskenlerini gunceller.

*sha1() - Diger fonksiyonlarin kullanildigi ve ana islemleri yapan fonksiyondur.
ilk for dongusu (metin boyutu)/(blok boyutu) kadar,yani blok sayi kadar donecek.
icerisindeki for dongusu 512bit=64byte buyukluguneki bloku doldurmak icin donecek.
elde edilen blok hashBlock fonksiyonuna gonderilerek hash degerleri guncellenecek.
Eger elde edilen blok son bloksa uzunluk bolgesine(64bitlik son bolum) tasmissa 
uzunluk degeri bir sonraki blokun sonuna eklenecektir.
En sonda H degerlerini kullanarak Hash degerini donduruyor.
