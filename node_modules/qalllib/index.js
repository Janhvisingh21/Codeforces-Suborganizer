let q = require('q')

let qSyncAll = function (functionName, nos, ...args) {
  nos = nos.concat([])
  let p = q()
  let thePromises = []

  nos.forEach(function (file) {
    p = p
      .then(function () {
        return functionName(file, ...args)
      })

      .catch(function (error) {
        return {
          data: error,
          flag: 'reject'
        }
      })
    thePromises.push(p)
  })

  return q.all(thePromises)
    .then(function (allResponses) {
      let data = {
        resolve: [],
        reject: []
      }
      allResponses.forEach(function (resp) {
        if (resp.flag == 'reject') {
          data.reject.push(resp.data)
        } else {
          data.resolve.push(resp)
        }
      })
      return data
    })
}

let qAsyncAll = function (functionName, nos, ...args) {
  let data = {
    resolve: [],
    reject: []
  }
  nos = nos.concat([])

  return q.all(nos.map(function (obj) {
    return functionName(obj , ...args).catch(function (error) {
      data.reject.push(error)
    })
  }))
    .then(function (allResponses) {
      allResponses.forEach(function (resp) {
        if (resp != null) {
          data.resolve.push(resp)
        }
      })
      return data
    })

    .catch(function (error) {
      data.reject.push(error)
      console.log(error, error, error)
    })
}

let qASyncWithBatch = function (functionName, nos, batchSize = 10, ...args) {
  let p = q()
  let thePromises = []
  nos = nos.concat([])

  let arrays = []
  while (nos.length > 0) { arrays.push(nos.splice(0, batchSize)) }

  arrays.forEach(function (file) {
    p = p
      .then(function () {
        return qAsyncAll(functionName, file, ...args)
      })

      .catch(function (error) {
        return {
          data: error,
          flag: 'reject'
        }
      })
    thePromises.push(p)
  })

  return q.all(thePromises)
    .then(function (allResponses) {
      let data = {
        resolve: [],
        reject: []
      }
      allResponses.forEach(function (resp) {
        if (resp.resolve.length > 0) {
          data.resolve = data.resolve.concat(resp.resolve)
        }
        if (resp.reject.length > 0) {
          data.reject = data.reject.concat(resp.reject)
        }
      })
      return data
    })
}

exports.qSyncAll = qSyncAll
exports.qAsyncAll = qAsyncAll
exports.qASyncWithBatch = qASyncWithBatch
