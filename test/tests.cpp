#include "gtest/gtest.h"

extern "C" {
#include "parser.h"
}

TEST(StructureOfAddress, DoubleSep) {
    char fake_structure[] = "user@mail@ru";
    ASSERT_EQ(check_email(fake_structure), -1);
}

TEST(StructureOfAddress, InvalidDomain) {
    char fake_domain[] = "tpark@mail..ru";
    ASSERT_EQ(check_email(fake_domain), -2);
}

TEST(StructureOfAddress, InvalidName) {
    char fake_name[] = ".use/r@mail.ru";
    ASSERT_EQ(check_email(fake_name), -3);
}

TEST(StructureOfAddress, ValidAddress) {
    char address[] = "user@google.com";
    ASSERT_EQ(check_email(address), 0);
}

TEST(ParseAddress, VaildParsing) {
    char address[] = "doparse@headhunter.ru";
    char valid_name[] = "doparse";
    char valid_postname[] = "headhunter";
    char valid_domain[] = ".ru";

    Email* email = parse(address);

    ASSERT_STREQ(email->name, valid_name);
    ASSERT_STREQ(email->postname, valid_postname);
    ASSERT_STREQ(email->domain, valid_domain);

    free_email(email);
}
