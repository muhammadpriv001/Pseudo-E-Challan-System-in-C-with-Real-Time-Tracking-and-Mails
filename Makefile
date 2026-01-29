# ====== Output Files ======
ADMIN_OUT = Admin/adminControls.out
CHALLAN_OUT = Challans/challan.out
PSEUDO_OUT = pseudo_echallan.out
REG_OUT = Registrations/registration.out
BANK_OUT = Finances/bank.out

# ====== Compiler & Flags ======
CXX = g++
CXXFLAGS = -std=gnu++17 -O2

# ====== Common Sources ======
COMMON = Functions/functions.cpp

# ====== Required Libraries ======
# OpenCV, Tesseract, Leptonica (common)
COMMON_LIBS = `pkg-config --cflags --libs opencv4 tesseract lept`
# Additional libraries for email (curl + SSL)
EMAIL_LIBS = -lcurl -lssl -lcrypto -pthread

# ====== Admin ======
admin: $(ADMIN_OUT)

$(ADMIN_OUT): Admin/adminControls.cpp $(COMMON)
	$(CXX) $(CXXFLAGS) Admin/adminControls.cpp $(COMMON) -o $(ADMIN_OUT) $(COMMON_LIBS) $(EMAIL_LIBS)

run-admin: admin
	./$(ADMIN_OUT)

# ====== Challan ======
challan: $(CHALLAN_OUT)

$(CHALLAN_OUT): Challans/challan.cpp $(COMMON)
	$(CXX) $(CXXFLAGS) Challans/challan.cpp $(COMMON) -o $(CHALLAN_OUT) $(COMMON_LIBS) $(EMAIL_LIBS)

run-challan: challan
	./$(CHALLAN_OUT)

# ====== Pseudo E-Challan ======
pseudo: $(PSEUDO_OUT)

$(PSEUDO_OUT): pseudo_echallan.cpp $(COMMON)
	$(CXX) $(CXXFLAGS) pseudo_echallan.cpp $(COMMON) -o $(PSEUDO_OUT) $(COMMON_LIBS) $(EMAIL_LIBS)

run-pseudo: pseudo
	./$(PSEUDO_OUT)

# ====== Registration ======
registration: $(REG_OUT)

$(REG_OUT): Registrations/registration.cpp $(COMMON)
	$(CXX) $(CXXFLAGS) Registrations/registration.cpp $(COMMON) -o $(REG_OUT) $(COMMON_LIBS) $(EMAIL_LIBS)

run-registration: registration
	./$(REG_OUT)

# ====== Bank System ======
bank: $(BANK_OUT)

$(BANK_OUT): Finances/bank.cpp $(COMMON)
	$(CXX) $(CXXFLAGS) Finances/bank.cpp $(COMMON) -o $(BANK_OUT) $(COMMON_LIBS) $(EMAIL_LIBS)

run-bank: bank
	./$(BANK_OUT)

# ====== Build Everything ======
all: admin challan pseudo registration bank

# ====== Clean ======
clean:
	rm -f $(ADMIN_OUT) $(CHALLAN_OUT) $(PSEUDO_OUT) $(REG_OUT) $(BANK_OUT)