import testplugin

# Пример вызова
result = testplugin.write_proto(
    "output.bin",
    "idfa:abc123",
    55.75,
    37.61,
    [1, 2, 3, 4, 5]
)

print("Write success:", result)