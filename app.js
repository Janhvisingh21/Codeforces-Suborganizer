const express = require('express'),
request = require('request'),
ejs = require('ejs'),
bodyParser = require('body-parser'),
fs = require('fs'),
cheerio = require('cheerio');

const app = express();
var handle;
var count = 0;
app.use(bodyParser.urlencoded({ extended: true }));
app.set('view engine', 'ejs');
app.setTimeout = 20000;

app.get('/', (req, res) => {
    res.render('index');
});

function addSubmission(submission) {
    var contestID = submission.contestId,
        submissionID = submission.id,
        index = submission.problem.index,
        problemName = submission.problem.name,
        programmingLanguage = submission.programmingLanguage;
    request('https://codeforces.com/contest/' + contestID + '/submission/' + submissionID, (error, response, body) => {
        if (!error && response.statusCode == 200) {
            const $ = cheerio.load(body);
            var content = $('#program-source-text').text();
            var extension;
            switch (programmingLanguage) {
                case "GNU C11":
                    extension = '.c';
                    break;
                case "Clang++17 Diagnostics":
                case "GNU C++11":
                case "GNU C++14":
                case "GNU C++17":
                case "MS C++":
                case "MS C++ 2017":
                    extension = '.cpp';
                    break;
                case "Java 8":
                    extension = '.java';
                    break;
                case "Python 2":
                case "Python 3":
                    extension = '.py';
                    break;
            }
            problemName = problemName.replace(/[^A-Z0-9]+/ig, "_");
            if (!fs.existsSync(`Codeforces Submissions - ${handle}` + '/' + contestID)) {
                fs.mkdirSync(`Codeforces Submissions - ${handle}` + '/' + contestID);
            }
            count--;
            if (content.length > 100) {
                console.log(contestID + ' ' + submissionID + ' done');
            }
            else {
                console.log(contestID + ' ' + submissionID);
                return;
            }
            fs.writeFileSync(`Codeforces Submissions - ${handle}/` + contestID + '/' + contestID + '-' + index + '-' + problemName + extension, content);
        }
        else {
            console.log(error);
        }
    });
}

app.post('/', (req, res) => {
    handle = req.body.handle;
    request('http://codeforces.com/api/user.status?handle=' + handle + '&from=1&count=2000', (error, response, body) => {
        if (!error && response.statusCode == 200) {
            var allSubmissions = JSON.parse(body)['result'];
            var acceptedSubmissions = allSubmissions.filter(element => element.verdict === 'OK');
            if (!fs.existsSync(`Codeforces Submissions - ${handle}`)) {
                fs.mkdirSync(`Codeforces Submissions - ${handle}`);
            }
            count = acceptedSubmissions.length;
            count--;
            console.log(count);
            var repeat = setInterval(() => {
                if (count >= 0) {
                    addSubmission(acceptedSubmissions[count]);
                }
                else {
                    clearInterval(repeat);
                }
            }, 20000);
            res.render('thank-you');
        }
        else {
            console.log(error);
            res.render('error', { error: error });
        }
    });
});

app.listen(3000, () => {
    console.log('Server started at port 3000!');
});