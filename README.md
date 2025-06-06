# Protofile Writer Extension

Простое расширение на C для записи сериализованных protobuf-сообщений в бинарный файл.

## 📌 Что реализовано
- Расширение `testplugin` с функцией `write_proto(filename, key, lat, lon, apps)`
- Используется структура `UserApps` из protobuf (`lat`, `lon`, `repeated apps`)
- Протобуф-сообщение сериализуется и записывается в файл


## ⚙️ Как собрать

```bash
python setup.py build_ext --inplace
```

## 🚀 Как использовать

```bash
python test.py
```

В файл `output.bin` будет записано сериализованное сообщение.

## 📄 Примечание
- `appsinstalled_pb2.py` должен быть сгенерирован из `appsinstalled.proto` через `protoc`
- Файл `output.bin` создаётся или дописывается в бинарном режиме (`ab`)

