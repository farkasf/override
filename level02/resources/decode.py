encrypted = ["756e505234376848", "45414a3561733951", "377a7143574e6758", "354a35686e475873", "48336750664b394d"]
decrypted = []

for seq in encrypted:
	decrypted.append(seq.decode("hex")[::-1])

password = "".join(decrypted)

print "flag: {}".format(password)
