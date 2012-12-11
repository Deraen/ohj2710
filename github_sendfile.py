#!/usr/bin/env python

import github3
import sys

from getpass import getpass

CREDENTIALS_FILE = '.githubtoken'


def login():
    user = raw_input('Username: ')
    password = ''

    while not password:
        password = getpass('Password for {0}: '.format(user))

    note = 'Ohj2710 autobuild uploader'
    note_url = 'https://github.com/Deraen/ohj2710'
    scopes = ['user', 'repo']

    auth = github3.authorize(user, password, scopes, note, note_url)
    print(auth)

    with open(CREDENTIALS_FILE, 'w') as fd:
        fd.write(auth.token)


token = ''
try:
    f = open(CREDENTIALS_FILE, 'r')
except IOError:
    login()

with open(CREDENTIALS_FILE, 'r') as fd:
    token = fd.readline().strip()

gh = github3.login(token=token)

r = gh.repository('Deraen', 'ohj2710')

if len(sys.argv) >= 2:
    download = r.create_download(sys.argv[1], sys.argv[2])
